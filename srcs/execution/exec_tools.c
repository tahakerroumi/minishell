/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:21:41 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/22 13:48:08 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
