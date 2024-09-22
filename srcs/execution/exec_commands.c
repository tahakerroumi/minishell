/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:54:38 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/22 18:11:03 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_path(t_command *cmd)
{
	struct stat st;

	if (access(cmd->argv[0], F_OK) != 0)
        no_such_f_d(cmd);
    else if (access(cmd->argv[0], X_OK) == 0)
	{
        if (stat(cmd->argv[0], &st) == 0)
		{
            if (S_ISDIR(st.st_mode))
                is_dir_cmd(cmd);
            else
                ft_execve(cmd);
        }
    }
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
		pathname = ft_strjoin(path[i], "/");
		tmp = pathname;
		pathname = ft_strjoin(tmp, cmd->argv[0]);
		free(tmp);
		if (!access(pathname, F_OK | X_OK))
		{
			cmd->path = pathname;
			ft_execve(cmd);
		}
		free(pathname);
		i++;
	}
	free_string_array(path);
    not_found(cmd);
}

void	exec_command(t_command *cmd)
{
	char	*getpath;

	getpath = ft_strdup(ft_getenv("PATH"));
	if (!getpath)
		return (ft_perror("malloc", 1));
	char **path = ft_split(getpath, ':'); // fix the split or make a new one if its needed
	free(getpath);
	if (!cmd->argv[0][0])
	{
		free_string_array(path);
        not_found(cmd);
	}
	exec(path, cmd);
}
