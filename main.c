/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ta7ino <ta7ino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 08:49:08 by ta7ino            #+#    #+#             */
/*   Updated: 2024/08/21 15:38:00 by ta7ino           ###   ########.fr       */
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

void	exec(char **env, char *prompt)
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

void	executable(char **env,char *prompt)
{
	int pid[2];
	
	// is heredoc
	
	// if pipe
	
	// is builtin
	
	// else is exec 
}

void	ft_start(char **env, char *prompt)
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

void	minishell(char **old_env)
{
	char	**env;
	char	*prompt;

	while (1)
	{
		prompt = readline("shymphony@land~> ");
		env = envir_copy(old_env);
		ft_start(env, prompt);
	}
}

int main(int ac, char **av, char **env)
{
	(void)ac;
    (void)av;
	if (ac != 1)
		return 0;
	minishell(env);
	return (0);
}