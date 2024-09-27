/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_env_key.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:26:56 by aattak            #+#    #+#             */
/*   Updated: 2024/09/26 16:27:26 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_env_key(char *key)
{
	size_t	i;

	if (key[0] != '_' && !ft_isalpha(key[0]))
		return (0);
	i = 1;
	while (key[i] == '_' || ft_isalnum(key[i]))
		i++;
	return (!((int)(key[i])));
}
