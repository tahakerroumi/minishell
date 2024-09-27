/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_int_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:41:32 by aattak            #+#    #+#             */
/*   Updated: 2024/09/21 11:17:14 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_int_words(int *ptr, int sep)
{
	size_t	i;
	size_t	count;

	if (!(ptr[0]))
		return (0);
	count = 0;
	if (ptr[0] != sep)
		count = 1;
	i = 1;
	while (ptr[i])
	{
		if (ptr[i - 1] == sep && ptr[i] != sep)
			count++;
		i++;
	}
	return (count);
}

static size_t	word_len(int *ptr, int sep)
{
	size_t	i;

	i = 0;
	while (ptr[i] && ptr[i] != sep)
		i++;
	return (i);
}

static int	*malloc_nd_fill(int *ptr, int sep, size_t *i)
{
	size_t	len;
	int		*word;

	while (ptr[*i] && ptr[*i] == sep)
		(*i)++;
	len = word_len(&ptr[*i], sep);
	word = (int *)ft_calloc(len + 1, sizeof(int));
	if (!word)
		return (NULL);
	ft_memcpy(word, &ptr[*i], len * sizeof(int));
	while (ptr[*i] && ptr[*i] != sep)
		(*i)++;
	return (word);
}

int	**split_int_ptr(int *ptr, int sep)
{
	size_t	i;
	size_t	j;
	size_t	n_words;
	int		**split;

	n_words = count_int_words(ptr, sep);
	split = (int **)ft_calloc(n_words + 1, sizeof(int *));
	if (!split)
		return (NULL);
	i = 0;
	j = 0;
	while (j < n_words)
	{
		split[j] = malloc_nd_fill(ptr, sep, &i);
		if (!(split[j]))
		{
			free_int_split(split);
			return (NULL);
		}
		j++;
	}
	return (split);
}
