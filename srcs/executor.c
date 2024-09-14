/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:43:25 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/14 18:55:26 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void ft_perror(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

pid_t ft_fork()
{
    pid_t pid = fork();
    if (pid < 0)
        ft_perror("fork");
    return pid;
}

// int	exec_builtin(t_command *cmd)
// {
//     if (strcmp(cmd->argv[0], "cd") == 0)
//         my_cd();
//     if (strcmp(cmd->argv[0], "echo") == 0)
//         my_echo();
//     if (strcmp(cmd->argv[0], "pwd") == 0)
//         my_pwd();
//     if (strcmp(cmd->argv[0], "export") == 0)
//         my_export();
// 	if (strcmp(cmd->argv[0], "unset") == 0)
//         my_unset();
//     if (strcmp(cmd->argv[0], "env") == 0)
//         my_env();
// 	if (strcmp(cmd->argv[0], "exit") == 0)
//         my_exit();
// 	return (0);
// }

void	ft_execve(t_command *cmd)
{
	if (execve(cmd->argv[0], cmd->argv, g_root.env) == -1)
		ft_perror("execve");
}

void	is_absolute(t_command *cmd)
{
	struct stat st;

	if (access(cmd->argv[0], F_OK) != 0) // F_OK  Used to check for the existence of a file.
        printf("symphony: %s: No such file or directory\n", cmd->argv[0]);
    else if (access(cmd->argv[0], X_OK) == 0) // X_OK flag: Used to check for execute permission bit.
	{
        if (stat(cmd->argv[0], &st) == 0)
		{
            if (S_ISDIR(st.st_mode))
                printf("symphony: %s: Is a directory\n", cmd->argv[0]);
            else if (S_ISREG(st.st_mode)) // S_ISREG is regular file
                ft_execve(cmd);
        }
    }
    else
        printf("symphony: %s: Permission denied\n", cmd->argv[0]);
}

char *move_path(char *path)
{
	char *str;
	int i;
	
	i = 0;
	while (path[i] != ':')
		i++;
	str = ft_strdup(path + i + 1);
	return (str);
}

char *envpath(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", ft_strlen("PATH")) == 0)
			return (move_path(env[i]));
		i++;
	}
	return (NULL);
}

void	exec(char **path, t_command *cmd)
{
	char	*pathname;
	char	*tmp;
	int i;

	i = 0;
	while (path[i])
	{
		pathname = ft_strjoin(path[i], "/");
		tmp = pathname;
		pathname = ft_strjoin(tmp, cmd->argv[0]);
		free(tmp);
		if (!access(pathname, F_OK | X_OK))
		{
			free(cmd->argv[0]);
			cmd->argv[0] = pathname;
			ft_execve(cmd);
		}
		free(pathname);
		i++;
	}
	// check if somehow no path was found
	if (access(pathname, F_OK | X_OK) == -1)
		printf("%s : Command not found\n", cmd->argv[0]);
}

void	executable(t_command *cmd)
{
	char *getpath = envpath(g_root.env);
	char **path = ft_split(getpath, ':');
	exec(path,cmd);
}

void	execute_command(t_command *cmd)
{
	int		exit_status;
	pid_t	pid;

// 1 - is builtin
// 2 - is abseloute starts with "/"
// 3 - is relative starts with "./"
// 4 - its a normal command.

	pid = ft_fork();
	if (pid == 0)
	{
		// if (exec_builtin(cmd))
		// 	return (0);
		if (ft_strrchr(cmd->argv[0], '/'))
			is_absolute(cmd);
		else
			executable(cmd);
	}
	waitpid(pid, &exit_status, 0);
}

int	number_commands(t_command *cmd)
{
	t_command *token;
	int i;

	i = 0;
	token = cmd;
	while (token)
	{
		i++;
		token = token->next;
	}
	return (i);
}

void    executor(t_command *cmd)
{
	cmd->max = number_commands(cmd);
	if (cmd->max > 1)
		printf("need to be done");
	else
		execute_command(cmd);
}
