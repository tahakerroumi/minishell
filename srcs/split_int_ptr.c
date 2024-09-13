/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_int_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:41:32 by aattak            #+#    #+#             */
/*   Updated: 2024/09/13 15:46:02 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	i;

	i = 0;
	if (count && size && (count > ((size_t)-1) / size))
		return (NULL);
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	while (i < count * size)
	{
		((char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (dst == src)
		return (dst);
	i = 0;
	while (i < n)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
	return (dst);
}

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

void	free_int_split(int **split)
{
	size_t	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
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
