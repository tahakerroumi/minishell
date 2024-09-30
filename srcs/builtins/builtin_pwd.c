/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:08:37 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/29 22:27:03 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(char **argv)
{
	char	*cwd;

	(void)argv;
	cwd = ft_getcwd();
	if (cwd)
	{
		ft_putstr_fd(cwd, 1);
		ft_putstr_fd("\n", 1);
		return (0);
	}
	perror("minishell: getcwd");
	return (1);
}
