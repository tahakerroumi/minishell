/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:14:11 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/20 16:05:40 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int execute_builtin(t_command *cmd)
{
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (builtin_env());
	else if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (builtin_echo(cmd));
	return (0);
}
