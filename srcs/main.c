/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:40:03 by aattak            #+#    #+#             */
/*   Updated: 2024/09/29 18:04:25 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_root	g_root;

int	main(int ac, char **av)
{
	(void)av;
	if (ac == 1)
	{
		init_signals(IN_PARENT);
		init_env();
		minishell_loop();
	}
	ft_putstr_fd(RED"minishell accepts no arguments\n"RESET, 2);
	return (1);
}
