/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:43:25 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/15 21:25:59 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// void	ft_putstr_fd(char *s, int fd)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		write(fd, &s[i], 1);
// 		i++;
// 	}
// }

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

void ft_pipe(int *fd)
{
    if (pipe(fd) == -1)
        ft_perror("pipe");
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

	if (access(cmd->argv[0], F_OK) != 0)// F_OK  Used to check for the existence of a file.
	{
		ft_putstr_fd("No such file or directory\n", 2);
		exit(127);
	} 
    else if (access(cmd->argv[0], X_OK) == 0) // X_OK flag: Used to check for execute permission bit.
	{
        if (stat(cmd->argv[0], &st) == 0)
		{
            if (S_ISDIR(st.st_mode))
				ft_putstr_fd("Is a directory\n", 2);
            else if (S_ISREG(st.st_mode)) // S_ISREG is regular file
                ft_execve(cmd);
        }
    }
    else
		ft_putstr_fd("Permission denied\n", 2);
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
		ft_putstr_fd("Command not found\n", 2);
}

void	executable(t_command *cmd)
{
	char *getpath = envpath(g_root.env);
	char **path = ft_split(getpath, ':');
	exec(path,cmd);
	return ;
}

void	red_filein(t_file *file)
{
	int fd;
	t_file *txt;

	txt = file;
	while (txt->type == FILE_IN)
	{
		if (!txt->next || txt->next->type != FILE_IN)
			break ;
		fd = open(txt->name, O_RDONLY);
		if (fd < 0)
		{
			ft_putstr_fd("No such file or directory\n", 2);
			exit(1);
		}
		close(fd);
		txt = txt->next;
	}
	fd = open(txt->name, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("No such file or directory\n", 2);
		exit(1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
		ft_perror("dup2");
	close(fd);
}

void	red_fileout(t_file *file)
{
	int fd;
	struct stat st;
	t_file *txt;

	txt = file;
	while (txt->type == FILE_OUT)
	{
		if (!txt->next || txt->next->type != FILE_OUT)
			break ;
		if (!stat(txt->name, &st) && S_ISDIR(st.st_mode))
		{
			printf("symphony: %s: Is a directory\n", txt->name);
			exit(1);
		}
		if (txt->type == FILE_APPEND)
			fd = open (txt->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (txt->type == FILE_OUT)
			fd = open (txt->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
		{
			ft_perror("open");
			exit(1);
		}
		close(fd);
		txt = txt->next;
	}
	if (!stat(txt->name, &st) && S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("Is a directory\n", 2);
		exit(1);
	}
	if (txt->type == FILE_APPEND)
		fd = open (txt->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (txt->type == FILE_OUT)
		fd = open (txt->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_perror("open");
		exit(1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
		ft_perror("dup2");
	close(fd);
}

void	redirections(t_command *cmd)
{
	t_file *txt;

	txt = cmd->file;
	while (txt)
	{
		if (txt->type == FILE_AMBIGUOUS)
		{
			ft_putstr_fd("ambiguous redirect", 2);
			exit(1);
		}
		if (txt->type == FILE_IN)
			red_filein(txt);
		if (txt->type == FILE_OUT || txt->type == FILE_APPEND)
			red_fileout(txt);
		txt = txt->next;
	}
}

void	execute_command(t_command *cmd)
{
	int		exit_status;
	pid_t	pid;

	// if (cmd->file)
	// 	redirections(cmd);
	// if (exec_builtin(cmd))
	pid = ft_fork();
	if (pid == 0)
	{
		if (cmd->file)
			redirections(cmd);
		if (ft_strrchr(cmd->argv[0], '/'))
			is_absolute(cmd);
		else
			executable(cmd);
		exit(1);
	}
	waitpid(pid, &exit_status, 0);
}

void	pipex(t_command *cmd)
{
	int			fd[cmd->max - 1][2];
	int i;
	int			pid[cmd->max];

	i = 0;
	while (i < cmd->max)
	{
		if (i < cmd->max - 1)
			ft_pipe(fd[i]);
		
	}
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
		pipex(cmd);
	else
		execute_command(cmd);
}
