/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:40:03 by aattak            #+#    #+#             */
/*   Updated: 2024/09/28 20:21:30 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

t_root	g_root;

int	main(int ac, char **av)
{
	(void)av;
	if (ac == 1)
	{
		// minishell_init(); // init shell variables like IFS
		// env_init();
		//g_root.env = __environ;
		// signals_init();
		signal(SIGQUIT, SIG_IGN);
		init_env();
		minishell_loop();
		rl_clear_history();
		free_string_array(g_root.env);
		printf("exit\n");
		////////////////////////////////close(3);/////////////////
		return (0);
	}
	ft_putstr_fd(RED"minishell accepts no arguments\n"RESET, 2);
	return (1);
}
