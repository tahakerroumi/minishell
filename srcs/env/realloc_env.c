/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:07:39 by aattak            #+#    #+#             */
/*   Updated: 2024/09/25 13:43:54 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	realloc_env(void)
{
	char	**new_env;

	g_root.env_size *= 2;
	new_env = (char **)malloc((g_root.env_size + 1) * sizeof(char *));
	if (!new_env)
	{
		perror("minishell: malloc: Cannot ReAllocate ENV");
		return (1);
	}
	ft_memcpy(new_env, g_root.env, g_root.env_count + 1);
	free(g_root.env);
	g_root.env = new_env;
	return (0);
}
