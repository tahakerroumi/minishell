/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:54:38 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/29 22:04:09 by aattak           ###   ########.fr       */
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

void	exec(char **path, t_command *cmd)
{
	char	*pathname;
	char	*tmp;
	int		i;

	i = 0;
	while (path[i])
	{
		if (path[i][0])
			pathname = ft_strjoin(path[i], "/");
		else
			pathname = ft_strjoin(".", "/");
		tmp = pathname;
		pathname = ft_strjoin(tmp, cmd->argv[0]);
		free(tmp);
		if (!access(pathname, F_OK | X_OK))
		{
			cmd->path = pathname;
			ft_execve(cmd, path);
		}
		free(pathname);
		i++;
	}
	free_string_array(path);
	not_found(cmd);
}

void	exec_command(t_command *cmd)
{
	char	**path;

	path = ft_split(ft_getenv("PATH"), ':');
	if (!path)
	{
		perror("minishell: malloc");
		exit(exit_cleanup(1));
	}
	if (!cmd->argv[0][0])
	{
		free_string_array(path);
		not_found(cmd);
	}
	exec(path, cmd);
}
