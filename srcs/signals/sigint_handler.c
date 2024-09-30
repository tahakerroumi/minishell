/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 09:17:44 by aattak            #+#    #+#             */
/*   Updated: 2024/09/30 03:38:55 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signal)
{
	if (signal == SIGINT && g_root.in_heredoc)
	{
		g_root.exit_status = 130;
		g_root.sigint = 1;
		g_root.in_heredoc = 0;
		if (ioctl(STDOUT_FILENO, TIOCSTI, "\n") == -1)
		{
			perror("minishell: ioctl");
			return ;
		}
	}
	else if (signal == SIGINT && !g_root.childs)
	{
		g_root.exit_status = 130;
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
