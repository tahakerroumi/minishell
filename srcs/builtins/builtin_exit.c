/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 21:39:02 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/30 03:34:02 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_converter(const char *nptr)
{
	size_t	i;
	int		signe;
	long	res;

	if (!nptr)
		return (0);
	i = 0;
	res = 0;
	signe = 1;
	while (ft_isspace(nptr[i]))
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

static int	is_word(char *s)
{
	int	i;

	i = 0;
	if (!s[i])
		return (1);
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			break ;
		i++;
	}
	while (ft_isspace(s[i]))
		i++;
	if (s[i])
		return (1);
	return (0);
}

int	exit_cleanup(int ret_val)
{
	rl_clear_history();
	free_string_array(g_root.env);
	free_commands(g_root.command, F_PATH | F_ARGV | F_FILE | F_COMMAND);
	stdio_files(RECOVER);
	return (ret_val);
}

int	builtin_exit(char **argv)
{
	long	num;

	ft_putstr_fd("exit\n", 2);
	if (!argv[1] && exit_cleanup(1))
		exit((unsigned char)g_root.exit_status);
	if (is_word(argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(exit_cleanup(2));
	}
	else if (argv[2])
	{
		ft_putstr_fd("minishell: exit:", 2);
		ft_putstr_fd(" too many arguments\n", 2);
		g_root.exit_status = 1;
		return (1);
	}
	num = ft_converter(argv[1]);
	exit((unsigned char)exit_cleanup((int)num));
}
