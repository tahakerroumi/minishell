/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:21:41 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/24 20:51:32 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_perror(char *msg, int child)
{
	perror(msg);
	if (child)
		exit(1);
	return (1);
}

int	ft_execve(t_command *cmd)
{
	if (cmd->path)
	{
		if (execve(cmd->path, cmd->argv, g_root.env) == -1)
			return (ft_perror("execve", 1));
	}
	else
	{
		if (execve(cmd->argv[0], cmd->argv, g_root.env) == -1)
			return (ft_perror("execve", 1));
	}
	return (0);
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
