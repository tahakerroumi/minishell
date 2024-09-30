/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:23:37 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/29 22:29:55 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_command *cmd)
{
	if (!cmd->argv[0])
		return (0);
	else if (ft_strcmp(cmd->argv[0], "cd") == 0)
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

int	create_pipes(t_command *cmd, int *fd)
{
	if (pipe(fd) == -1)
	{
		perror("minishell: pipe");
		return (1);
	}
	cmd->pipefd[1] = fd[1];
	cmd->pipefd[2] = fd[0];
	cmd->next->pipefd[0] = fd[0];
	return (0);
}

int	create_childs(t_command *cmd)
{
	cmd->pid = fork();
	if (!cmd->pid)
		child_routine(cmd);
	if (cmd->pipefd[0])
		close(cmd->pipefd[0]);
	if (cmd->pipefd[1])
		close(cmd->pipefd[1]);
	if (cmd->pid == -1)
	{
		perror("minishell: fork");
		return (1);
	}
	g_root.childs += 1;
	return (0);
}

int	executor(t_command *cmd)
{
	int			fd[2];

	while (cmd->next)
	{
		if (create_pipes(cmd, fd))
			break ;
		if (create_childs(cmd))
			break ;
		cmd = cmd->next;
	}
	if (cmd->pipefd[0] || (cmd->argv[0] && !is_builtin(cmd)))
	{
		create_childs(cmd);
		g_root.exit_status = waiting(g_root.command);
	}
	else
	{
		stdio_files(SAVE);
		if (handle_files(cmd->file))
			return (1);
		g_root.exit_status = execute_builtin(cmd);
		stdio_files(RECOVER);
	}
	return (0);
}
