/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri_l.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:20:16 by aattak            #+#    #+#             */
/*   Updated: 2024/09/24 11:31:42 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_striteri_l(char *str, size_t len, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	while (str && f && i < len)
	{
		f(i, str + i);
		i++;
	}
}
