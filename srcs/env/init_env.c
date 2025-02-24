/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:35:46 by aattak            #+#    #+#             */
/*   Updated: 2024/09/29 14:06:41 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_env_size(char **env)
{
	size_t	env_size;

	env_size = 0;
	while (env && env[env_size])
		env_size++;
	return (env_size);
}

void	init_env(void)
{
	size_t	i;

	g_root.env_size = get_env_size(__environ);
	g_root.env_count = g_root.env_size;
	g_root.env = (char **)malloc((g_root.env_size + 1) * sizeof(char *));
	if (!g_root.env)
	{
		perror("minishell: malloc: Cannot Allocate ENV");
		return ;
	}
	i = 0;
	while (__environ[i])
	{
		g_root.env[i] = ft_strdup(__environ[i]);
		if (!g_root.env[i])
		{
			perror("minishell: malloc: Cannot Allocate Full ENV");
			return ;
		}
		i++;
	}
	g_root.env[i] = NULL;
}
