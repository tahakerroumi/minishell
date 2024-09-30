/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdio_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 12:03:04 by aattak            #+#    #+#             */
/*   Updated: 2024/09/29 18:49:02 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	stdio_files(int flag)
{
	static int	fd[2];

	if (flag == SAVE)
	{
		fd[0] = dup(STDIN_FILENO);
		if (fd[0] == -1)
			perror("minishell: dup");
		fd[1] = dup(STDOUT_FILENO);
		if (fd[1] == -1)
			perror("minishell: dup");
	}
	else if (flag == RECOVER)
	{
		if (fd[0] && fd[0] != -1 && dup2(fd[0], STDIN_FILENO) == -1)
			perror("minishell: dup2");
		if (fd[0] && fd[0] != -1 && close(fd[0]) == -1)
			perror("minishell: close");
		if (fd[1] && fd[1] != -1 && dup2(fd[1], STDOUT_FILENO) == -1)
			perror("minishell: dup2");
		if (fd[1] && fd[1] != -1 && close(fd[1]) == -1)
			perror("minishell: close");
		fd[0] = 0;
		fd[1] = 0;
	}
}
