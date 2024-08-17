/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 08:49:08 by ta7ino            #+#    #+#             */
/*   Updated: 2024/08/17 21:35:16 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char *get_path(char **env,char *str)
{
    int i = -1;
    while (env[++i])
    {
        if (ft_strncmp(env[i], str, ft_strlen(str)) == 0)
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
	char *str;
	while (path[i])
	{
		if (!access(command,F_OK))
		{
			ft_free_double(path);
			return (command);
		}
		str = ft_strjoin(path[i], command);
		if (!access(str,F_OK))
		{
			ft_free_double(path);
			free(command);
			return (str);
		}
		free(str);
		i++;
	}
	free(command);
	ft_free_double(path);
	return (NULL);
}

void	executable(char **env, char *prompt)
{
	char *cmd;
    char *envpath = get_path(env,"PATH");
    char **path = split_path(envpath);
	char **command = ft_split(prompt,' ');
	cmd = ft_strjoin("/",command[0]);
	char *exec = check_exec(path, cmd); // exec first arg;
	if (!exec)
	{
		free(exec);
		ft_free_double(command);
		printf("%s: command not found\n",prompt);
		return ;
	}
	if (execve(exec,command,env) == -1)
	{
		free(exec);
		ft_free_double(command);
		printf("%s command not found\n",prompt);
	}
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