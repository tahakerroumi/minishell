/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 00:50:33 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/05 05:12:15 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	int fd[2];
	int pid;
	int pid2;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (0);
	}
	
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);

		char *cmd1[] = {"/bin/ls", NULL};
		if (execve(cmd1[0],cmd1,NULL) == -1)
		{
			perror("execve");
			return (2);
		}
	}
	
	pid2 = fork();
	if (pid2 == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid2 == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);

		char *cmd2[] = {"/bin/wc", "-l", NULL};
		if (execve(cmd2[0],cmd2,NULL) == -1)
		{
			perror("execve");
			return (2);
		}
	}
	close(fd[0]);
	close(fd[1]);

	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	return 0;
}