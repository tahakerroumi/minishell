/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:19:35 by aattak            #+#    #+#             */
/*   Updated: 2024/09/27 14:58:21 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// export var=hello
// export var    // this one must do nothing
// if (!ft_strchr(argv[i], '=') && ft_getenv(argv[i])) => then do nothing

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
