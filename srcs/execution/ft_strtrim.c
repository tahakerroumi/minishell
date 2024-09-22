/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:30:43 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/22 14:43:12 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	checkchar(char a, char  *b)
{
	int	i;

	i = ft_strlen(b);
	while (i >= 0)
	{
		if (b[i] == a)
			return (1);
		i--;
	}
	return (0);
}
static char	*ft_substr(char  *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;
	size_t	slen;

	i = 0;
	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	if (len > slen - start)
		len = slen - start;
	p = malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	while (start + i < slen && i < len)
	{
		p[i] = s[start + i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
char	*ft_strtrim(char  *s1, char  *set)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1)
		return (ft_strdup(""));
	if (!set)
		return ((char *)s1);
	i = 0;
	j = ft_strlen(s1);
	while (s1[i] && checkchar(s1[i], set))
		i++;
	while (j > 0 && checkchar(s1[j - 1], set))
		j--;
	if (i >= j)
	{
		return (ft_strdup(""));
	}
	str = ft_substr(s1, i, j - i);
	return (str);
}


