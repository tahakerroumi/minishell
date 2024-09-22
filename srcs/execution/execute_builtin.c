/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:14:11 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/22 14:43:44 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int execute_builtin(t_command *cmd)
{
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (builtin_echo(cmd));
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (builtin_exit(cmd));
	return (0);
}
