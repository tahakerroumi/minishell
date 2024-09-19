/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:23:37 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/19 14:54:35 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(t_command *cmd)
{
    if (ft_strcmp(cmd->argv[0], "cd") == 0)
        return (1);
    else if (ft_strcmp(cmd->argv[0], "echo") == 0)
        return (1);
    else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
        return (1);
    else if (ft_strcmp(cmd->argv[0], "export") == 0)
        return (1);
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
        return (1);
    else if (ft_strcmp(cmd->argv[0], "env") == 0)
        return (1);
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
        return (1);
	return (0);
}

void	run_builtin(t_command *cmd)
{
    if (ft_strcmp(cmd->argv[0], "pwd") == 0)
        my_pwd();
}

void	pipex(t_command *cmd, int *fd)
{
	while (cmd->next)
	{
		ft_pipe(fd);
		cmd->pipefd[1] = fd[1];
		cmd->pipefd[2] = fd[0];
		cmd->next->pipefd[0] = fd[0];

		cmd->pid = ft_fork();
		if (!cmd->pid)
			child_routine(cmd);
		if (cmd->pipefd[0])
			close(cmd->pipefd[0]);
        if (cmd->pipefd[1])
			close(cmd->pipefd[1]);
		cmd = cmd->next;
	}
}

void	executing(t_command *cmd, t_command *head)
{
		cmd->pid = ft_fork();
		if (!cmd->pid)
			child_routine(cmd);
		if (cmd->pipefd[0])
            close(cmd->pipefd[0]);
		if (cmd->pipefd[1])
			close(cmd->pipefd[1]);
		g_root.exit_status = waiting(head);
}

void    execution(t_command *head)
{
	int			fd[2];
	t_command	*cmd;

	cmd = head;
	if (cmd->next)
		pipex(cmd, fd);
	if (cmd->pipefd[0] || (cmd->argv[0] && !is_builtin(cmd)))
		executing(cmd, head);
	else
		run_builtin(cmd);
}
