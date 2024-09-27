/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:20:23 by aattak            #+#    #+#             */
/*   Updated: 2024/09/26 18:38:14 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

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
