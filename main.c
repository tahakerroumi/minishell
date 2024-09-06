/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 00:50:33 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/06 07:16:20 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_of_env(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**envir_copy(char **env)
{
	char	**my_env;
	int		i;

	i = 0;
	my_env = (char **)ft_calloc(sizeof(char *), len_of_env(env) + 1);
	if (!my_env)
		return (NULL);
	while(env[i])
	{
		my_env[i] = ft_strdup(env[i]);
		i++;
	}
	my_env[i] = NULL;
	return (my_env);
}

void	pipex(char ***cmd, char **env)
{
	int fd[2];
	int pid;
	
	pid = fork();
	if (pid == 0)
	{
		if (!*(cmd + 1))
		{
			dup2(fd[0], 0);
			
		}
		if (pipe(fd) == -1)
		{
			perror("pipe");
			exit(1);
		}
		
	}
	else if (pid == -1)
	{
		perror("fork");
		return (0);
	}
	else if (pid > 0)
	{
		// parent part	
	}
}

int main(int ac , char **av, char **env)
{
	char **envir;
	envir = envir_copy(env);
	char *ls[] = {"/bin/ls", "-la", NULL};
	char *ps[] = {"/bin/ps", NULL};
	char *wc[] = {"/bin/wc", "-c"};
	char **cmnds[] = {ls, ps, wc, NULL};
	pipex(cmnds, env);
	return (0); 
}