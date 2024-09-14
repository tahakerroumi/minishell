/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:12:22 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/14 18:44:49 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i])
// 		i++;
// 	return (i);
// }

int	ft_strncmp(char *s1,  char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

// char	*ft_strdup(const char *s)
// {
// 	char	*p;
// 	char	*t;
// 	size_t	len;

// 	len = ft_strlen((char *)s);
// 	p = (char *)malloc((sizeof(char) * (len + 1)));
// 	if (!p)
// 		return (NULL);
// 	t = p;
// 	while (*s)
// 	{
// 		*p++ = *s++;
// 	}
// 	*p = '\0';
// 	return (t);
// }

char	*ft_strrchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	while (i >= 0)
	{
		if (s[i] == (unsigned char)c)
			return ((char *)(s + i));
		i--;
	}
	if ((unsigned char)c == '\0')
		return ((char *)(s + i));
	return (NULL);
}