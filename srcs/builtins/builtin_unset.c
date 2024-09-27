/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:30:12 by aattak            #+#    #+#             */
/*   Updated: 2024/09/26 15:36:29 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(char **argv)
{
	size_t	i;

	i = 1;
	while (argv[i])
	{
		if (is_valid_env_key(argv[i]))
			ft_unsetenv(argv[i]);
		i++;
	}
	return (0);
}
