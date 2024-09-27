/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:07:24 by aattak            #+#    #+#             */
/*   Updated: 2024/09/27 18:56:01 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_loop()
{
	char		*command_line;

	g_root.end_loop = 0; /////////// delete me
	while (!g_root.end_loop)
	{
		printf("\n\n"); ////////////////////// delete me
		command_line = readline(GREEN"Shymphony@Land ~> "RESET);
		if (!command_line) ////////// means the user clicked on ctrl+d
			g_root.end_loop = 1;
		g_root.command = parser(command_line);
		if (!g_root.command)
			continue ;

		///// handle heredocs after forming commands
		g_root.sigint = 0;


		/////////////////////////////////////////////////////////
		print_commands(g_root.command); ///////////////////


		command_iter(g_root.command, handle_heredocs);

		if (execution(g_root.command))
		{
			// cleanup all of it
			continue;
		}

		free_commands(g_root.command, F_PATH | F_ARGV | F_FILE | F_COMMAND);//
		printf("\n\nexit = [%d]\n\n", g_root.exit_status);
		/////////////////////////////////////////////////////////
	}
}
