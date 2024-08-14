/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 08:49:08 by ta7ino            #+#    #+#             */
/*   Updated: 2024/08/14 21:10:12 by tkerroum         ###   ########.fr       */
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
    char **new_path = ft_split(old_path + i + 1,':');
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
		i++;
	}
	return (NULL);
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
		return ;
	}
	int one = execve(exec,command,env);
	printf("SUCCESS");
	if (one == -1)
		printf("%s command not found\n",prompt);
}

void	minishell(char **env, char *prompt)
{
	pid_t pid;
	// if (!ft_strncmp(prompt,"exit",5))
	// {
		// implement exit
	// }
	// else
	// {
	pid = fork();
	if (pid == 0)
		executable(env,prompt);
	else
	{
		int status;
		waitpid(pid,&status,0);
	}
	// }
}

int main(int ac, char **av, char **env)
{
	(void)ac;
    (void)av;
	char *prompt;
	while (1)
	{
		prompt = readline("taha's shell:~ ");
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