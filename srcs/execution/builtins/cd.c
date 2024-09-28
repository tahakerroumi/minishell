/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 09:16:03 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/28 18:53:57 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getcwd(void)
{
	static char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)))
		return (cwd);
	return (NULL);
}

int	change_dir(char **args)
{
	char	*cwd;

	cwd = ft_strjoin("OLDPWD=", ft_getcwd());
	if (!args[1])
	{
		if (chdir(getenv("HOME")))
			return (free(cwd), ft_perror("cd", 0));
	}
	else if (chdir(args[1]))
		return (free(cwd), ft_perror("cd", 0));
	if (ft_putenv(cwd))
		return (free(cwd), 1);
	free(cwd);
	cwd = ft_strjoin("PWD=", ft_getcwd());
	if (ft_putenv(cwd))
		return (free(cwd), 1);
	return (free(cwd), 0);
}

int builtin_cd(char **args)
{
	if (!getenv("HOME") && !args[1])
	{
		return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	}
    else if (args[1] && args[2])
		return (too_many_args(args));
	return (change_dir(args));
}
