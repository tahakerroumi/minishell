/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:43:25 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/13 18:48:27 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//extern __environ;

void ft_perror(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

void	ft_execve(t_command *cmd)
{
	if (execve(cmd->argv[0] , cmd->argv, __environ) == -1)
		ft_perror("execve");
}


pid_t ft_fork()
{
    pid_t pid = fork();
    if (pid < 0)
        ft_perror("fork");
    return pid;
}

int is_builtin(t_command *cmd)
{
    if (strcmp(cmd->argv[0], "cd") == 0)
        return (1);
    if (strcmp(cmd->argv[0], "echo") == 0)
        return (1);
    if (strcmp(cmd->argv[0], "pwd") == 0)
        return (1);
    if (strcmp(cmd->argv[0], "export") == 0)
        return (1);
	if (strcmp(cmd->argv[0], "unset") == 0)
        return (1);
    if (strcmp(cmd->argv[0], "env") == 0)
        return (1);
	if (strcmp(cmd->argv[0], "exit") == 0)
        return (1);
	return (0);
}

int	check_absolute(t_command *cmd)
{
	if (!ft_strchr('/'))
		return (0);
}

void    executor(t_command *cmd)
{
    pid_t   pid;
    int     exit_status;     

    pid = ft_fork();
    if (pid == 0)
    {
        if (cmd->next)
            ft_pipes(cmd);
        if (is_builtin)
            ft_built(cmd);
		if (check_absolute(cmd))
			exec_absolute(cmd);
        else
            ft_executable(cmd);
    }
    else
        waitpid(pid, &exit_status, 0);
}
