/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:19:35 by aattak            #+#    #+#             */
/*   Updated: 2024/09/29 14:45:10 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_putenv(char *var)
{
	char	*eos;

	eos = ft_strchr(var, '=');
	if (eos)
		*eos = '\0';
	else if (ft_getenv(var))
		return (0);
	ft_unsetenv(var);
	if (eos)
		*eos = '=';
	if (g_root.env_size == g_root.env_count && realloc_env())
		return (1);
	g_root.env[g_root.env_count] = ft_strdup(var);
	if (!g_root.env[g_root.env_count])
	{
		perror("minishell: malloc:");
		return (1);
	}
	g_root.env_count++;
	g_root.env[g_root.env_count] = NULL;
	return (0);
}
