/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:21:41 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/18 18:50:26 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_perror(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

void	ft_execve(t_command *cmd)
{
	if (cmd->path)
	{
		if (execve(cmd->path, cmd->argv, g_root.env) == -1)
			ft_perror("execve");
	}
	else
	{
		if (execve(cmd->argv[0], cmd->argv, g_root.env) == -1)
			ft_perror("execve");
	}
}

pid_t ft_fork()
{
    pid_t pid = fork();
    if (pid < 0)
        ft_perror("fork");
    return (pid);
}

void ft_pipe(int *fd)
{
    if (pipe(fd) == -1)
        ft_perror("pipe");
}
int	waiting(t_command *cmd)
{
	int	exit_status;

	while (cmd)
	{
		waitpid(cmd->pid, &exit_status, 0);
		cmd = cmd->next;
	}
	return (WEXITSTATUS(exit_status));
}
