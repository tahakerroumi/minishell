/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:20:23 by aattak            #+#    #+#             */
/*   Updated: 2024/09/26 12:11:30 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unsetenv(char *key)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(key);
	i = 0;
	while (g_root.env && g_root.env[i])
	{
		if (g_root.env[i][0] == key[0] && !ft_memcmp(g_root.env[i], key, len)
			&& (g_root.env[i][len] == '=' || g_root.env[i][len] == '\0'))
		{
			free(g_root.env[i]);
			g_root.env[i] = g_root.env[g_root.env_count - 1];
			g_root.env[g_root.env_count - 1] = NULL;
			g_root.env_count--;
			return (0);
		}
		i++;
	}
	return (1);
}
