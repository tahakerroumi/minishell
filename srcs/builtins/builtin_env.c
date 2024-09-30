/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:17:52 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/29 15:20:26 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(char **argv)
{
	int	i;

	(void)argv;
	i = 0;
	while (g_root.env && g_root.env[i])
	{
		if (ft_strchr(g_root.env[i], '='))
		{
			ft_putstr_fd(g_root.env[i], 1);
			ft_putstr_fd("\n", 1);
		}
		i++;
	}
	return (0);
}
