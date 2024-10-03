/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:07:24 by aattak            #+#    #+#             */
/*   Updated: 2024/09/30 11:35:15 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_loop(void)
{
	char		*command_line;

	while (1)
	{
		g_root.command = NULL;
		command_line = readline("Shymphony@Land ~> ");
		if (!command_line)
			builtin_exit((char *[]){"exit", NULL});
		if (parser(command_line))
			continue ;
		if (command_iter(g_root.command, handle_heredocs))
			continue ;
		if (executor(g_root.command))
		{
			g_root.exit_status = 1;
			stdio_files(RECOVER);
		}
		free_commands(g_root.command, F_PATH | F_ARGV | F_FILE | F_COMMAND);
	}
}
