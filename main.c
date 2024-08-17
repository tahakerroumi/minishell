/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 08:49:08 by ta7ino            #+#    #+#             */
/*   Updated: 2024/08/17 11:50:13 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_path(char **env)
{
    int i = -1;
    while (env[++i])
    {
        if (ft_strncmp(env[i],"PATH",4) == 0)
            return (env[i]);
    }
    return (NULL);
}

int move_path(char *str)
{
    int i = 0;
    while (str[i] && str[i] != ':')
        i++;
    return (i);
}

char **split_path(char *old_path)
{
    int i = move_path(old_path);
    char **new_path = ft_split(old_path + i + 1, ':');
    return (new_path);
}

char	*check_exec(char **path,char *command)
{
	int i = 0;
	while (path[i])
	{
		if (!access(command,F_OK))
			return (command);
		char *str = ft_strjoin(path[i], command);
		if (!access(str,F_OK))
			return (str);
		free(str);
		i++;
	}
	return (NULL);
}

void	ft_free_double(char **str)
{
	int i = 0;
	
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	executable(char **env, char *prompt)
{
	char *cmd;
    char *envpath = get_path(env);
    char **path = split_path(envpath);
	char **command = ft_split(prompt,' ');
	cmd = ft_strjoin("/",command[0]);
	char *exec = check_exec(path, cmd); // exec first arg;
	if (!exec)
	{
		printf("%s: command not found\n",prompt);
		free(cmd);
		ft_free_double(path);
		return ;
	}
	// free(cmd);
	// ft_free_double(path);
	int one = execve(exec,command,NULL);
	if (one == -1)
		printf("%s command not found\n",prompt);
}

void	minishell(char **env, char *prompt)
{
	pid_t pid;
	if (!ft_strncmp(prompt,"exit",5))
	{
		free(prompt);
		exit(0);
	}
	else
	{
		pid = fork();
		if (pid == 0)
			executable(env,prompt);
		else
		{
			int status;
			waitpid(pid,&status,0);
			printf("\n%d\n",status);
		}
	}
}

int main(int ac, char **av, char **env)
{
	(void)ac;
    (void)av;
	char *prompt;
	while (1)
	{
		prompt = readline("shymphony@land ~> ");
		if (!prompt)
			return (0);
		if (ft_strlen(prompt) > 0)
		{
			add_history(prompt);
			minishell(env,prompt);
		}
		free(prompt);
	}
	return (0);
}