/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:15:44 by aattak            #+#    #+#             */
/*   Updated: 2024/09/26 16:28:06 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_export(void)
{
	size_t	i;

	i = 0;
	while (g_root.env[i])
	{
		ft_putstr_fd("export ", 1);
		ft_putstr_fd(g_root.env[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	return (0);
}

static int	handle_export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid idetifier\n", 2);
	return (1);
}

int	builtin_export(char **argv)
{
	int		is_valid;
	size_t	i;
	char	*eos;
	int		ret_val;

	i = 1;
	ret_val = 0;
	if (!(argv[i]))
		return (print_export());
	while (argv[i])
	{
		eos = ft_strchr(argv[i], '=');
		if (eos)
			*eos = '\0';
		is_valid = is_valid_env_key(argv[i]);
		if (eos)
			*eos = '=';
		if (is_valid)
			ft_putenv(argv[i]);
		else
			ret_val = handle_export_error(argv[i]);
		i++;
	}
	return (ret_val);
}
