/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 09:16:03 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/29 22:26:18 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	too_many_args(char **cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(": too many arguments\n", 2);
	return (1);
}

char	*ft_getcwd(void)
{
	static char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)))
		return (cwd);
	return (NULL);
}

static int	change_dir(char **argv)
{
	char	*cwd;

	cwd = ft_strjoin("OLDPWD=", ft_getcwd());
	if (!argv[1] && chdir(ft_getenv("HOME")))
		return (free(cwd), perror("minishell: cd"), 1);
	else if (argv[1] && chdir(argv[1]))
		return (free(cwd), perror("minishell: cd"), 1);
	if (cwd)
		ft_putenv(cwd);
	free(cwd);
	cwd = ft_strjoin("PWD=", ft_getcwd());
	if (cwd)
		ft_putenv(cwd);
	free(cwd);
	return (0);
}

int	builtin_cd(char **argv)
{
	if (!ft_getenv("HOME") && !argv[1])
		return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	else if (argv[1] && argv[2])
		return (too_many_args(argv));
	return (change_dir(argv));
}
