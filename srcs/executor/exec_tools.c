/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:21:41 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/30 10:30:03 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execve(t_command *cmd, char **path)
{
	if (cmd->path && execve(cmd->path, cmd->argv, g_root.env) == -1)
	{
		perror("minishell: execve");
		free(path[0]);
		free(path);
		exit(exit_cleanup(1));
	}
	else if (execve(cmd->argv[0], cmd->argv, g_root.env) == -1)
	{
		perror("minishell: execve");
		exit(exit_cleanup(1));
	}
}

int	waiting(t_command *cmd)
{
	int	exit_status;
	int	sig_int;

	sig_int = 0;
	while (g_root.childs)
	{
		waitpid(cmd->pid, &exit_status, 0);
		g_root.childs -= 1;
		if (WIFSIGNALED(exit_status) && WTERMSIG(exit_status == 2))
			sig_int++;
		cmd = cmd->next;
	}
	if (sig_int)
		ft_putstr_fd("\n", 2);
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	else if (WIFSIGNALED(exit_status))
	{
		exit_status = WTERMSIG(exit_status) + 128;
		if (exit_status == 131)
			ft_putstr_fd("Quit (core dumped)\n", 2);
		else if (exit_status == 139)
			ft_putstr_fd("Segmentation fault (core dumped)\n", 2);
	}
	return (exit_status);
}
