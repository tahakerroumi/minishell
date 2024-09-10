/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:09:24 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/10 16:59:47 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_perror(char *str)
{
	perror(str);
	exit(1);
}

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

int	pipex(char ***cmd, char **env, int num)
{
	int n = num - 1;
	int fd[n][2];
	int exit_status;
	int pid;
	int i = 0;
	int pids[num];

	while (*cmd)
	{
		if (i < n && pipe(fd[i]) == -1)
			ft_perror("pipe");
		pids[i] = fork();
		if (pids[i] < 0)
			ft_perror("fork");
		if (pids[i] == 0)
		{
			if (i == 0)
			{
				dup2(fd[i][1], STDOUT_FILENO);
				close(fd[i][1]);
				close(fd[i][0]);
			}
			else if (!*(cmd + 1))
			{
				close(fd[i - 1][1]);
				dup2(fd[i - 1][0], STDIN_FILENO);
				close(fd[i - 1][0]);
			}
			else
			{
				close(fd[i - 1][1]);
				dup2(fd[i - 1][0], STDIN_FILENO);
				close(fd[i - 1][0]);
				dup2(fd[i][1], STDOUT_FILENO);
				close(fd[i][1]);
				close(fd[i][0]);
			}
			execve(*cmd[0], *cmd, env);
			ft_perror("execve");
		}
		else
		{
			if (i > 0)
			{
				close(fd[i - 1][0]);
				close(fd[i - 1][1]);
			}
		}
		i++;
		cmd++;
	}
	i = 0;
	while (i < num)
	{
		waitpid(pids[i], &exit_status, 0);
		i++;
	}
	return (exit_status);
}

int main(int ac, char **av, char **env)
{
    int i;
    char **envir;

    envir = envir_copy(env);
    char *ls[] = {"/bin/caddt", NULL};
    char *pwd[] = {"/bin/cat", "-e",  NULL};
    char *o[] = {"/bin/pwd",  NULL};
    char *nomore[] = {"/bin/wc", "-l",  NULL};
    char *fr[] = {"/bin/lsds", "-la",  NULL};
    char **cmds[] = {ls, pwd, o, nomore, fr, NULL};
    i = pipex(cmds, envir, 5);
	printf("\n\n%d\n\n", i);
}
