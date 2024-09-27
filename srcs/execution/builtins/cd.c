/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 09:16:03 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/27 18:51:13 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*current_wc(void)
{
	char	cwd[4096];
	char	*pwd;

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		pwd = ft_strdup(cwd);
		return (pwd);
	}
	else
		return (NULL);
}

static char	*join_env(char *env, char *value)
{
	char *tmp;
	char *result;

	tmp = ft_strjoin(env, "=");
	result = ft_strjoin(tmp, value);
	return (free(value), free(tmp), result);
}

int	change_dir(char **args)
{
	char	*cwd;

	cwd = join_env("OLDPWD", current_wc());
	if (!args[1])
	{
		if (chdir(getenv("HOME")))
		{
			ft_perror("chdir", 0);
			return (free(cwd), 1);
		}
		if (ft_putenv(cwd))
			return (free(cwd), 1);
		free(cwd);
	}
	else
	{
		if (chdir(args[1]))
		{
			ft_perror("chdir", 0);
			return (free(cwd), 1);
		}
		if (ft_putenv(cwd))
			return (free(cwd), 1);
		free(cwd);
	}
	cwd = join_env("PWD", current_wc());
	if (ft_putenv(cwd))
		return (free(cwd), 1);
	return (free(cwd), 0);
}

int builtin_cd(char **args)
{
    if (args[1] && args[2])
	{
        return (too_many_args(args));
	}
	if (!args[1])
	{
		if (!getenv("HOME"))
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
		change_dir(args);
		// pwd = join_env("OLDPWD", current_wc());
		// if (chdir(getenv("HOME")) != 0)
		// {
		// 	ft_perror("chdir", 0);
		// 	free(pwd);
		// }
		// if (ft_putenv(pwd))
		// 	return (free(pwd), 1);
		// free(pwd);
		// pwd = join_env("PWD", current_wc());
		// ft_putenv(pwd);
		// free(pwd);
	}
	else
	{
		change_dir(args);
	}
	return (0);
}
