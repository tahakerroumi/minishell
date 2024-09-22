/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:37:11 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/22 16:16:07 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	permission_file_error(t_file *file, int child)
{
    ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file->name, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	if (child)
		exit(1);
	g_root.exit_status = 1;
	return (0);
}

int	is_dir_error(t_file *file, int child)
{
    ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file->name, 2);
	ft_putstr_fd(": Is a directory\n", 2);
	if (child)
		exit(1);
	g_root.exit_status = 1;
	return (0);
}

int	no_file_dir(t_file *file, int child)
{
    ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file->name, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	if (child)
		exit(1);
	g_root.exit_status = 1;
	return (0);
}

int	ambigious_error(t_file *file, int child)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file->name, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	if (child)
		exit(1);
	g_root.exit_status = 1;
	return (0);
}
