/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:09:24 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/14 11:29:37 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = 0;
		i++;
	}
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*p;
	char	*t;
	size_t	len;

	len = ft_strlen((char *)s);
	p = (char *)malloc((sizeof(char) * (len + 1)));
	if (!p)
		return (NULL);
	t = p;
	while (*s)
	{
		*p++ = *s++;
	}
	*p = '\0';
	return (t);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	if (size && nmemb > SIZE_MAX / size)
		return (NULL);
	if (!nmemb || !size)
		return (ft_strdup(""));
	p = malloc(nmemb * size);
	if (!p)
		return (NULL);
	ft_bzero(p, nmemb * size);
	return (p);
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

// void	ft_perror(char *str)
// {
// 	perror(str);
// 	exit(1);
// }

// int	pipex(char ***cmd, char **env, int num)
// {
// 	int n = num - 1;
// 	int fd[n][2];
// 	int exit_status;
// 	int pid;
// 	int i;

// 	i = 0;
// 	while (*cmd)
// 	{
// 		if (i < n && (pipe(fd[i]) == -1))
// 			ft_perror("perror");
// 		pid = fork();
// 		if (pid < 0)
// 			ft_perror("fork");
// 		if (pid == 0)
// 		{
// 			if (i == 0)
// 			{
// 				dup2(fd[i][1],STDOUT_FILENO);
// 				close(fd[i][1]);
// 				close(fd[i][0]);
// 			}
// 			if (!*(cmd + 1))
// 			{
// 				close(fd[i - 1][1]);
// 				dup2(fd[i - 1][0], STDIN_FILENO);
// 				close(fd[i - 1][0]);
// 			}
// 			else
// 			{
// 				close(fd[i - 1][1]);
// 				dup2(fd[i - 1][0], STDIN_FILENO);
// 				close(fd[i - 1][0]);
// 				dup2(fd[i][1],STDOUT_FILENO);
// 				close(fd[i][1]);
// 				close(fd[i][0]);
// 			}
// 			execve(*cmd[0], *cmd, env);
// 			ft_perror("execve");
// 		}
// 		else	
// 		{
// 			if (i > 0)
// 			{
// 				close(fd[i - 1][0]);
// 				close(fd[i - 1][1]);
// 			}
// 		}
// 		i++;
// 		cmd++;
// 	}
// 	waitpid(pid, &exit_status, 0);
// 	i = 0;
// 	while (i < n)
// 	{
// 		close(fd[i][0]);
// 		close(fd[i][1]);
// 		i++;
// 	}
// 	return(exit_status);
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

void	close_fds(int *fd, int i)
{
	if (i > 0)
	{
		close(fd[0]);
		close(fd[1]);
	}
}

void	ft_dup2_w(int *fd)
{
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	close(fd[0]);
}

void	ft_dup2_r(int *fd)
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
}

void	ft_execve(char **cmd, char **env)
{
	if (execve(cmd[0], cmd, env) == -1)
		ft_perror("execve");
}

int	ft_waitpid(int *pid, int num)
{
	int exit_status;
	int i;

	i = -1;
	while (++i < num)
		waitpid(pid[i], &exit_status, 0);
	return (exit_status);
}
// int	pipex(char ***cmd, char **env, int num)
// {
// 	int fd[num - 1][2];  // Pipes array
// 	int i = 0;
// 	int pids[num];       // Store process IDs for each command

// 	while (i < num)
// 	{
// 		if (i < num - 1) // Create a pipe if not the last command
// 			ft_pipe(fd[i]);

// 		pids[i] = ft_fork();
// 		if (pids[i] == 0)  // Child process
// 		{
// 			// First command (only writes to the pipe)
// 			if (i == 0 && num > 1)
// 				ft_dup2_w(fd[i]);

// 			// Last command (only reads from the previous pipe)
// 			else if (i == num - 1 && num > 1)
// 				ft_dup2_r(fd[i - 1]);

// 			// Middle commands (if more than two commands are used)
// 			else if (i > 0 && i < num - 1)
// 			{
// 				ft_dup2_r(fd[i - 1]);
// 				ft_dup2_w(fd[i]);
// 			}

// 			ft_execve(cmd[i], env);  // Execute the command
// 		}

// 		// Parent process closes the pipes after use
// 		if (i > 0)  // Close previous pipe in the parent
// 		{
// 			close(fd[i - 1][0]);
// 			close(fd[i - 1][1]);
// 		}

// 		i++;
// 	}

// 	return (ft_waitpid(pids, num));  // Wait for all child processes
// }

int	pipex(char ***cmd, char **env, int num)
{
	int fd[num - 1][2];
	int i = 0;
	int pids[num];

	while (i < num)
	{
		if (cmd[i + 1])
			ft_pipe(fd[i]);
		pids[i] = ft_fork();
		if (pids[i] == 0)
		{
			if (i == 0)
				ft_dup2_w(fd[i]);
			else if (!cmd[i + 1])
				ft_dup2_r(fd[i - 1]);
			else
			{
				ft_dup2_r(fd[i - 1]);
				ft_dup2_w(fd[i]);
			}
			ft_execve(cmd[i], env);
		}
		else
			close_fds(fd[i - 1], i);
		i++;
	}
	return (WEXITSTATUS(ft_waitpid(pids, num)));
}

int main(int ac, char **av, char **env)
{
    int i;
    char **envir;

    envir = envir_copy(env);
    char *cmd1[] = {"/bin/caasdt", NULL};
    char *cmd2[] = {"/bin/cat",  "-e",NULL};
    // char *cmd3[] = {"/bin/pwd",  NULL};
    // char *cmd4[] = {"/bin/wc", "-l",  NULL};
    // char *cmd5[] = {"/bin/lsds", "-la",  NULL};
    char **cmds[] = {cmd1, cmd2 ,NULL};
    i = pipex(cmds, envir, 2);
	printf("\n\n%d\n\n", i);
}
