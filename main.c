/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 09:21:55 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/07 15:59:49 by tkerroum         ###   ########.fr       */
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

void    check_if_exec(char *str, char **env)
{
    int pid;
    int exit_status;
    char *cmd;
    char *envpath = get_path(env,"PATH");
    char **path = split_path(envpath);
	char **command = ft_split(str,' ');
	cmd = ft_strjoin("/",command[0]);
	char *exec = check_exec(path, cmd); // exec first arg;
	if (!exec)
	{
		free(exec);
		ft_free_double(command);
		printf("%s: command not found\n",str);
		return ;
	}
    pid = fork();
    if (pid == 0)
	{
        if (execve(exec,command,env) == -1)
	    {
		    free(exec);
		    ft_free_double(command);
		    printf("%s command not found\n",str);
	    }
    }
    else
        while (!wait(&exit_status))
            continue ;
}

void    prepare_to_execute(char *str, char **env)
{
    // builtins here
    
    if (!strncmp(str, "exit", 5))
    {
        free(str);
        exit(1);
    }
    else
        check_if_exec(str, env);
}

int pi(char *str)
{
    int count;
    int i;

    i  = 0;
    count = 0;
    while (str[i])
    {
        if (str[i] == '|')
            count++;
        i++;
    }
    return (count);
}

void    pipex(char *str, char **env)
{
    char ***cmnds;
    *cmnds = 
}

int main(int ac, char **av, char **env)
{
    char *prompt;
    int pipes;
    char **envir;

    if (ac != 1 || av[1])
        return (0);
    envir = envir_copy(env);
    while (1)
    {
        prompt = readline("shymphony> ");
        pipes = pi(prompt);
        if (!pipes)
            prepare_to_execute(prompt, envir);
        else
            pipex(prompt, env);
    }
}