/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ta7ino <ta7ino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:38:08 by ta7ino            #+#    #+#             */
/*   Updated: 2024/08/20 13:39:01 by ta7ino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_of_env(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**envir_copy(char **env)
{
	char	**my_env;
	int		i;

	i = 0;
	my_env = (char **)ft_calloc(sizeof(char *), len_of_env(env) + 1);
	if (!my_env)
		return (NULL);
	while(env[i])
	{
		my_env[i] = ft_strdup(env[i]);
		i++;
	}
	my_env[i] = NULL;
	return (my_env);
}