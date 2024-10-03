/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:40:03 by aattak            #+#    #+#             */
/*   Updated: 2024/09/30 08:09:11 by aattak           ###   ########.fr       */
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
	ft_putstr_fd("minishell accepts no arguments\n", 2);
	return (1);
}
