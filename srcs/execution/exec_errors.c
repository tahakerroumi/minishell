/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:01:18 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/19 16:20:26 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    no_such_f_d(t_command *cmd)
{
    ft_putstr_fd("minishell: " ,2);
    ft_putstr_fd(cmd->argv[0] ,2);
    ft_putstr_fd(": No such file or directory\n", 2);
	exit(127);
}

void    is_dir_cmd(t_command *cmd)
{
    ft_putstr_fd("minishell: " ,2);
    ft_putstr_fd(cmd->argv[0] ,2);
    ft_putstr_fd(": Is a directory\n", 2);
	exit(126);
}

void    no_permission(t_command *cmd)
{
    ft_putstr_fd("minishell: " ,2);
    ft_putstr_fd(cmd->argv[0] ,2);
    ft_putstr_fd(": Permission denied\n", 2);
	exit(126);
}

void    not_found(t_command *cmd)
{
    ft_putstr_fd("minishell: " ,2);
    ft_putstr_fd(cmd->argv[0] ,2);
	ft_putstr_fd(": Command not found\n", 2);
	exit(127);
}
