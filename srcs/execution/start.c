/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:23:37 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/20 23:44:43 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(t_command *cmd)
{
	if (!cmd->argv[0])
		return (0);
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

void	many_commands(t_command *cmd, int *fd)
{
	if (pipe(fd) == -1)
        ft_perror("pipe");
	cmd->pipefd[1] = fd[1];
	cmd->pipefd[2] = fd[0];
	cmd->next->pipefd[0] = fd[0];
	executing(cmd);
}

void	executing(t_command *cmd)
{
	cmd->pid = fork();
	if (cmd->pid < 0)
		ft_perror("fork");
	if (!cmd->pid)
		child_routine(cmd);
	if (cmd->pipefd[0])
        close(cmd->pipefd[0]);
	if (cmd->pipefd[1])
		close(cmd->pipefd[1]);
}

void    execution(t_command *head)
{
	int			fd[2];
	t_command	*cmd;

	cmd = head;
	while (cmd->next)
	{
		many_commands(cmd, fd);
		cmd = cmd->next;
	}
	if (cmd->pipefd[0] || (cmd->argv[0] && !is_builtin(cmd)))
	{
		executing(cmd);
		g_root.exit_status = waiting(head);
	}
	else
	{
		// save_stdio();
		// handle_files(cmd->file);
		g_root.exit_status = execute_builtin(cmd);
		// reset_stdio();
	}
	// close heredocs using cmd_iter and file_iter
}
