/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:23:37 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/18 22:03:29 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char **free_double(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

void	red_fileout(t_file *file)
{
	int		fd;
	struct	stat st;

	if (file->type == FILE_OUT  || file->type == FILE_APPEND)
	{
		if (!stat(file->name, &st) && S_ISDIR(st.st_mode))
		{
			ft_putstr_fd("Is a directory\n", 2);
			exit(1);
		}
		else if (access(file->name, X_OK) != 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(file->name, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			exit(1);
		}
		else
		{
			if (file->type == FILE_APPEND)
				fd = open (file->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
			else // if (file->type == FILE_OUT)
				fd = open (file->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd < 0)
				ft_perror("open");
			if (dup2(fd, STDOUT_FILENO) < 0)
			{
				close(fd);
				ft_perror("dup2");
			}
			close(fd);
		}
	}
}

void	red_filein(t_file *file)
{
	int fd;

// HANDLE HEREDOC HERE
	if (file->type == FILE_IN)
	{
		if (access(file->name, F_OK) != 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(file->name, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			exit(1);
		}
		else if (access(file->name, R_OK) != 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(file->name, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			exit(1);
		}
		else
		{
			fd = open(file->name, O_RDONLY);
			if (fd < 0)
				ft_perror("open");
			if (dup2(fd, STDIN_FILENO) < 0)
			{
				close(fd);
				ft_perror("dup2");
			}
			close(fd);
		}
	}
}

void	handle_files(t_file *head)
{
	t_file *file;

	file = head;
	while (file)
	{
		if (file->type == FILE_AMBIGUOUS)
		{
			ft_putstr_fd("ambiguous redirect\n", 2);
			exit(1);
		}
		if (file->type == FILE_IN || file->type == FILE_HEREDOC)
			red_filein(file);
		if (file->type == FILE_OUT || file->type == FILE_APPEND)
			red_fileout(file);
		file = file->next;
	}
}

void	handle_pipes(int *pipefd)
{
	if (pipefd[0])
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
	if (pipefd[1])
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	if (pipefd[2])
		close(pipefd[2]);
}

void	exec_path(t_command *cmd)
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
			{
				ft_putstr_fd("Is a directory\n", 2);
				exit(126);
			}
            else if (S_ISREG(st.st_mode)) // S_ISREG is regular file
                ft_execve(cmd);
        }
    }
    else
	{
		ft_putstr_fd("Permission denied\n", 2);
		exit(126);
	}
}

void	exec(char **path, t_command *cmd)
{
	char	*pathname;
	char	*tmp;
	int		i;

	i = 0;
	while (path[i])
	{
		pathname = ft_strjoin(path[i], "/");
		tmp = pathname;
		pathname = ft_strjoin(tmp, cmd->argv[0]);
		free(tmp);
		if (!access(pathname, F_OK | X_OK))
		{
			cmd->path = pathname;
			ft_execve(cmd);
		}
		free(pathname);
		i++;
	}
	// check if somehow no path was found
	free_argv(path);
	ft_putstr_fd("Command not found\n", 2);
	exit(127);
}

void	exec_command(t_command *cmd)
{
	char	*getpath;

	getpath = ft_strdup(ft_getenv("PATH"));
	if (!getpath)
		ft_perror("malloc");
	char **path = ft_split(getpath, ':'); // fix the split or make a new one if its needed
	free(getpath);
	if (!cmd->argv[0][0])
	{
		free_argv(path);
		ft_putstr_fd("Command not found\n", 2);
		exit(127);
	}
	exec(path, cmd);
}

void	execute(t_command *cmd)
{
	// if its a builtin
	if (ft_strchr(cmd->argv[0], '/') || !ft_getenv("PATH"))
		exec_path(cmd);
	else
		exec_command(cmd);
}

void	init_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	child_routine(t_command *cmd)
{
	init_signals();
	handle_pipes(cmd->pipefd);
	handle_files(cmd->file);
	if(cmd->argv[0])
		execute(cmd);
	exit(0);
}

int	is_builtin(t_command *cmd)
{
    if (ft_strcmp(cmd->argv[0], "cd") == 0)
        return (1);
    else if (ft_strcmp(cmd->argv[0], "echo") == 0)
        return (1);
    else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
        return (1);
    else if (ft_strcmp(cmd->argv[0], "export") == 0)
        return (1);
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
        return (1);
    else if (ft_strcmp(cmd->argv[0], "env") == 0)
        return (1);
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
        return (1);
	return (0);
}

void    execution(t_command *head)
{
	int			fd[2];
	t_command	*cmd;

	cmd = head;
	while (cmd->next)
	{
		ft_pipe(fd);
		cmd->pipefd[1] = fd[1];
		cmd->pipefd[2] = fd[0];
		cmd->next->pipefd[0] = fd[0];

		cmd->pid = ft_fork();
		if (!cmd->pid)
			child_routine(cmd);
		if (cmd->pipefd[0])
			close(cmd->pipefd[0]);
        if (cmd->pipefd[1])
			close(cmd->pipefd[1]);
		cmd = cmd->next;
	}
	if (cmd->pipefd[0] || (cmd->argv[0] && !is_builtin(cmd)))
	{
		cmd->pid = ft_fork();
		if (!cmd->pid)
			child_routine(cmd);
		if (cmd->pipefd[0])
            close(cmd->pipefd[0]);
		if (cmd->pipefd[1])
			close(cmd->pipefd[1]);
		g_root.exit_status = waiting(head);
	}
	// else is builtin
}
