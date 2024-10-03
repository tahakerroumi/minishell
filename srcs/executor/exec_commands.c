/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:54:38 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/30 10:40:06 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_path(t_command *cmd)
{
	struct stat	st;

	if (access(cmd->argv[0], F_OK) == -1)
		no_such_f_d(cmd);
	else if (stat(cmd->argv[0], &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
			is_dir_cmd(cmd);
	}
	else
	{
		perror("minishell: stat");
		exit(exit_cleanup(1));
	}
	if (access(cmd->argv[0], X_OK) == 0)
		ft_execve(cmd, NULL);
	else
		no_permission(cmd);
}

static char	*build_pathname(char **path, int i, char *arg)
{
	char	*pathname;
	char	*tmp;

	if (path[i][0])
		pathname = ft_strjoin(path[i], "/");
	else
		pathname = ft_strdup("./");
	if (!pathname)
	{
		perror("minishell: malloc");
		free(path[0]);
		free(path);
		exit(exit_cleanup(1));
	}
	tmp = pathname;
	pathname = ft_strjoin(pathname, arg);
	free(tmp);
	if (!pathname)
	{
		perror("minishell: malloc");
		free(path[0]);
		free(path);
		exit(exit_cleanup(1));
	}
	return (pathname);
}

void	exec(char **path, t_command *cmd)
{
	char	*pathname;
	int		i;

	i = 0;
	while (path[i])
	{
		pathname = build_pathname(path, i, cmd->argv[0]);
		if (!access(pathname, F_OK | X_OK))
		{
			cmd->path = pathname;
			ft_execve(cmd, path);
		}
		free(pathname);
		i++;
	}
	free(path[0]);
	free(path);
	not_found(cmd);
}

void	exec_command(t_command *cmd)
{
	char	*tmp;
	char	**path;

	if (!cmd->argv[0][0])
		not_found(cmd);
	tmp = ft_strdup(ft_getenv("PATH"));
	if (!tmp)
	{
		perror("minishell: malloc");
		exit(exit_cleanup(1));
	}
	path = custom_split(tmp, ':');
	if (!path)
	{
		free(tmp);
		perror("minishell: malloc");
		exit(exit_cleanup(1));
	}
	exec(path, cmd);
}
