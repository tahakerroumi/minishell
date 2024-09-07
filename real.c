/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   real.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 00:50:33 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/07 11:44:02 by tkerroum         ###   ########.fr       */
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

void pipex(char ***cmd, char **env , int **fds , int i )
{

    int pid;
	int exit_status;

    if (!(cmd[i]))  // Base case: no more commands
        return;

	if (i != 2)
		pipe(fds[i]) ; 
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(1);
    }
    if (pid == 0)  // Child process
    {
        if (i == 0) // If there's another command
        {
            close(fds[i][0]);  // Close the read end of the pipe
            dup2(fds[i][1], STDOUT_FILENO);  // Redirect stdout to the write end of the pipe
            close(fds[i][1]);  // Close the write end after duplicating
        }
        if ( i == 1 ) // Last command
        {
			close(fds[i - 1 ][1]);
            dup2(fds[i - 1 ][0], STDIN_FILENO);  // Redirect stdin to the read end of the pipe
			close(fds[i - 1 ][0]);
			dup2(fds[i][1], STDOUT_FILENO);
			close(fds[i][1]);
             // Close the read end after duplicating
        }
		if (i == 2 )
		{
			close(fds[i  -  1][1]);
            dup2(fds[i - 1][0], STDIN_FILENO);  // Redirect stdout to the write end of the pipe
            close(fds[i - 1][0]);

		}

        if (execve(cmd[i][0], cmd[i], env) == -1)
        {
            perror("execve");
            exit(1);
        }
    }
	else
	{
		pipex(cmd, env, fds , i + 1 );
		while(!wait(&exit_status))
		;
		if (i == 2)
		{ // Wait for the child process to finish
			printf("(%d ) \n" , exit_status );
  		// Recurse with the next command
		}
		i = 0;
		while(i < 2)
		{
			close(fds[i][0]) ;
			close(fds[i][1]) ;
			i++;
		}
	}
}

int main(int ac , char **av, char **env)
{
	char **en;
	en = envir_copy(env);
	int **fds;


	fds = malloc (sizeof(int*)*2) ; 
	fds[0] = malloc(sizeof(int)*2) ; 
	fds[1] =  malloc(sizeof(int)*2) ;

	// create a readline and let her 
	char *ls[] = {"/bin/ls", "-la", NULL};
	char *ps[] = {"/bin/pwd", NULL};
	char *wc[] = {"/usr/bin/wc", "-l",  NULL};
	char **cmnds[] = {ls, ps, wc, NULL};
	pipex(cmnds, en, fds ,  0  );
	return (0); 
}