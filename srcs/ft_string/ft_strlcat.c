/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:44:13 by aattak            #+#    #+#             */
/*   Updated: 2024/09/29 16:44:27 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!dst && !dstsize)
		return (ft_strlen(src));
	if (dstsize <= ft_strlen(dst))
		return (ft_strlen(src) + dstsize);
	while (dst[i])
		i++;
	while (src[j] && dstsize > i + 1)
		dst[i++] = src[j++];
	dst[i] = '\0';
	while (src[j++])
		i++;
	return (i);
}
