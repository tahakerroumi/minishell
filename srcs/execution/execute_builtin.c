/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:14:11 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/24 20:51:38 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_builtin(t_command *cmd)
{
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (builtin_echo(cmd));
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (builtin_exit(cmd));
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (builtin_env());
	return (0);
}
