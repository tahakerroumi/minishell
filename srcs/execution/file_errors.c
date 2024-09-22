/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:37:11 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/22 14:43:27 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    permission_file_error(t_file *file)
{
    ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file->name, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	exit(1);
}

void    is_dir_error(t_file *file)
{
    ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file->name, 2);
	ft_putstr_fd(": Is a directory\n", 2);
	exit(1);
}

void    no_file_dir(t_file *file)
{
    ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file->name, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	exit(1);
}

void	ambigious_error(t_file *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file->name, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	exit(1);
}
