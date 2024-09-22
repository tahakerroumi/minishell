/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:23:37 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/22 14:06:19 by tkerroum         ###   ########.fr       */
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

void	create_pipes(t_command *cmd, int *fd)
{
	if (pipe(fd) == -1)
        ft_perror("pipe");
		//cleanup : close herdocs and free command list
	cmd->pipefd[1] = fd[1];
	cmd->pipefd[2] = fd[0];
	cmd->next->pipefd[0] = fd[0];
}

void	executing(t_command *cmd)
{
	cmd->pid = fork();
	if (cmd->pid < 0)
		ft_perror("fork");
		//cleanup : close herdocs and free command list
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
		create_pipes(cmd, fd);
		executing(cmd);
		cmd = cmd->next;
	}
	if (cmd->pipefd[0] || (cmd->argv[0] && !is_builtin(cmd)))
	{
		executing(cmd);
		g_root.exit_status = waiting(head);
	}
	else
	{
		// save_stdio(); if (FAILURE) => perror then //cleanup : close herdocs and free command list
		// handle_files(cmd->file);
		g_root.exit_status = execute_builtin(cmd);
		// reset_stdio(); if (FAILURE) => perror then //cleanup : close herdocs and free command list
	}
	// close heredocs using cmd_iter and file_iter
}
