/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:19:39 by aattak            #+#    #+#             */
/*   Updated: 2024/09/29 14:45:48 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ilen(int nbr)
{
	size_t	len;

	len = 0;
	while (nbr > 0)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

static char	*exit_status(void)
{
	int			nbr;
	static char	str[15];
	size_t		len;

	nbr = g_root.exit_status;
	if (!nbr)
		return ("0");
	len = 0;
	if (nbr < 0)
	{
		nbr *= -1;
		str[0] = '-';
		len = 1;
	}
	len += ilen(nbr);
	str[len--] = '\0';
	while (nbr > 0)
	{
		str[len] = (nbr % 10) + '0';
		nbr /= 10;
		len--;
	}
	return (str);
}

char	*ft_getenv(const char *name)
{
	char	*var;
	char	**tmp;

	if (name && name[0] == '?' && name[1] == '\0')
		return (exit_status());
	tmp = __environ;
	__environ = g_root.env;
	var = getenv(name);
	__environ = tmp;
	return (var);
}
