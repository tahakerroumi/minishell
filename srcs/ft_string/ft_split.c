/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:26:39 by aattak            #+#    #+#             */
/*   Updated: 2024/09/29 16:40:55 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_count_words(char const *s, char c)
{
	size_t	i;
	size_t	count;

	if (!(s[0]))
		return (0);
	count = 0;
	if (s[0] != c)
		count = 1;
	i = 1;
	while (s[i])
	{
		if (s[i - 1] == c && s[i] != c)
			count++;
		i++;
	}
	return (count);
}

static size_t	word_len(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

static char	*malloc_nd_fill(char const *s, char c, size_t *i)
{
	size_t	len;
	char	*split;

	while (s[*i] == c && s[*i] != '\0')
		(*i)++;
	len = word_len(&s[*i], c);
	split = (char *)malloc(len + 1);
	if (!split)
		return (NULL);
	ft_strlcpy(split, &s[*i], len + 1);
	while (s[*i] != c && s[*i] != '\0')
		(*i)++;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	n_words;
	char	**split;

	if (!s)
		return (NULL);
	n_words = ft_count_words(s, c);
	split = (char **)ft_calloc((n_words + 1), sizeof(char *));
	if (!split)
		return (NULL);
	i = 0;
	j = 0;
	while (j < n_words)
	{
		split[j] = malloc_nd_fill(s, c, &i);
		if (!(split[j]))
		{
			free_string_array(split);
			return (NULL);
		}
		j++;
	}
	split[n_words] = NULL;
	return (split);
}
