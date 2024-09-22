/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:17:52 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/22 14:44:06 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	builtin_env(void)
{
	char	**envi;
	int		i;

	i = 0;
	envi = g_root.env;
	while (envi[i])
	{
		ft_putstr_fd(envi[i] ,1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	return (0);
}
