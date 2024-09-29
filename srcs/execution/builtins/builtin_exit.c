/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 21:39:02 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/29 15:21:33 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_converter(const char *nptr)
{
	long	i;
	int		signe;
	long	res;

	if (!nptr)
		return (0);
	i = 0;
	res = 0;
	signe = 1;
	while ((nptr[i] == 32) || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			signe = -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	return (res * signe);
}

static int	word(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (s[0] == '+' || s[0] == '-')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (1);
		i++;
	}
	return (0);
}

int	builtin_exit(char **argv)
{
	long	num;

	ft_putstr_fd("exit\n", 2);
	if (!argv[1])
	{
		exit(g_root.exit_status);
	}
	if (word(argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(2);
	}
	else if (argv[2])
	{
		ft_putstr_fd("minishell: exit:", 2);
		ft_putstr_fd(" too many arguments\n", 2);
		g_root.exit_status = 1;
		return (1);
	}
	num = ft_converter(argv[1]);
	exit((unsigned char)num);
}
