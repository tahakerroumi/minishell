/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:23:37 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/17 18:26:41 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	len = ft_strlen((char *)src);
	if (size == 0)
		return (len);
	size--;
	while (i < size && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	str = (char *)malloc((sizeof(char)) * (ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1));
	if (!str)
		return (NULL);
	ft_strcpy(str, s1);
	i = 0;
	while (s2[i])
	{
		str[ft_strlen((char *)s1) + i] = s2[i];
		i++;
	}
	str[ft_strlen((char *)s1) + i] = '\0';
	return (str);
}

void ft_perror(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

void	ft_execve(t_command *cmd)
{
	if (cmd->path)
	{
		if (execve(cmd->path, cmd->argv, g_root.env) == -1)
			ft_perror("execve");
	}
	else
	{
		if (execve(cmd->argv[0], cmd->argv, g_root.env) == -1)
			ft_perror("execve");
	}
}

pid_t ft_fork()
{
    pid_t pid = fork();
    if (pid < 0)
        ft_perror("fork");
    return (pid);
}

void ft_pipe(int *fd)
{
    if (pipe(fd) == -1)
        ft_perror("pipe");
}

void	red_fileout(t_file *file)
{
	int fd;
	struct stat st;
	t_file *txt;

	txt = file;
	if (txt->type == FILE_OUT  || txt->type == FILE_APPEND)
	{
		if (!stat(txt->name, &st) && S_ISDIR(st.st_mode))
		{
			printf("symphony: %s: Is a directory\n", txt->name);
			exit(1);
		}
		if (txt->type == FILE_APPEND)
			fd = open (txt->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else // if (txt->type == FILE_OUT)
			fd = open (txt->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
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

void	red_filein(t_file *file)
{
	int fd;
	t_file *txt;

// HANDLE HEREDOC HERE
	txt = file;
	if (txt->type == FILE_IN)
	{
		// check if the file exists and i have permissions on it
		fd = open(txt->name, O_RDONLY);
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

void	handle_files(t_file *head)
{
	t_file *file;

	file = head;
	while (file)
	{
		if (file->type == FILE_AMBIGUOUS)
		{
			ft_putstr_fd("ambiguous redirect", 2);
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

void	is_path(t_command *cmd)
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
	{
		ft_putstr_fd("Permission denied\n", 2);
		exit(1);
	}
}

// char *move_path(char *path)
// {
// 	char *str;
// 	int i;
	
// 	i = 0;
// 	while (path[i] != ':')
// 		i++;
// 	str = ft_strdup(path + i + 1);
// 	return (str);
// }

// char *envpath(char **env)
// {
// 	int i;

// 	i = 0;
// 	while (env[i])
// 	{
// 		if (ft_strncmp(env[i], "PATH", ft_strlen("PATH")) == 0)
// 			return (move_path(env[i]));
// 		i++;
// 	}
// 	return (NULL);
// }

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
			cmd->path = pathname;
			ft_execve(cmd);
		}
		free(pathname);
		i++;
	}
	// check if somehow no path was found
	ft_putstr_fd("Command not found\n", 2);
	exit(1);
}

void	is_command(t_command *cmd)
{
	char *getpath = ft_getenv("PATH");
	if (!getpath)
		return ; // check all the errors
	getpath = ft_strdup(getpath);
	if (!getpath)
		return ; // check all the errors
	char **path = ft_split(getpath, ':'); // fix the split or make a new one if its needed
	exec(path,cmd);
	return ;
}

void	execute(t_command *cmd)
{
	// if its a builtin
	if (ft_strchr(cmd->argv[0], '/'))
		is_path(cmd);
	else
		is_command(cmd);
	exit(1);
}

void	child_routine(t_command *cmd)
{
	// if (cmd->next)
	handle_pipes(cmd->pipefd);
	handle_files(cmd->file);
	execute(cmd);
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

int	waiting(t_command *head, t_command *cmd)
{
	//int tmp;
	int	exit_status;

	waitpid(cmd->pid, &exit_status, 0);
	head = head->next;
	while (head)
	{
		wait(NULL);
		// if (wait(&tmp) == cmd->pid)
		// 	exit_status = tmp;
		head = head->next;
	}
	return (exit_status);
}

void    execution(t_command *head)
{
	int		exit_status;
	int		fd[2];
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
	if (cmd->pipefd[0] || !is_builtin(cmd))
	{
		cmd->pid = ft_fork();
		if (!cmd->pid)
			child_routine(cmd);
		if (cmd->pipefd[0])
            close(cmd->pipefd[0]);
		if (cmd->pipefd[1])
			close(cmd->pipefd[1]);
		// waitpid(cmd->pid, &exit_status, 0);
		exit_status = waiting(head, cmd);
	}
	// else is builtin
}
