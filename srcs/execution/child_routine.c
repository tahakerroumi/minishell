/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:50:08 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/20 12:27:00 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute(t_command *cmd)
{
	if (is_builtin(cmd))
		exit(execute_builtin(cmd));
	if (ft_strchr(cmd->argv[0], '/') || !ft_getenv("PATH"))
		exec_path(cmd);
	else
		exec_command(cmd);
}

void	handle_files(t_file *head)
{
	t_file *file;

	file = head;
	while (file)
	{
		if (file->type == FILE_AMBIGUOUS)
            ambigious_error(file);
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
