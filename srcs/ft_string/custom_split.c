/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 06:41:20 by aattak            #+#    #+#             */
/*   Updated: 2024/09/30 09:12:05 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_words(char *string, char del)
{
	size_t	index;
	size_t	count;

	count = 1;
	index = 0;
	while (string[index])
	{
		if (string[index] == del)
			count++;
		index++;
	}
	return (count);
}

static void	extract_words(char **split, char *string, char del)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	split[j++] = string;
	while (string[i])
	{
		if (string[i] == del)
		{
			string[i] = '\0';
			split[j] = &string[i + 1];
			j++;
		}
		i++;
	}
	split[j] = NULL;
}

char	**custom_split(char *string, char del)
{
	size_t	count;
	char	**split;

	if (!string)
		return (NULL);
	count = count_words(string, del);
	split = (char **)malloc((count + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	extract_words(split, string, del);
	return (split);
}
