/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:53:34 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/30 00:49:19 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	outfile_checker(t_file *file)
{
	struct stat	st;

	if (!access(file->name, F_OK))
	{
		if (!stat(file->name, &st))
		{
			if (S_ISDIR(st.st_mode))
				return (is_dir_error(file));
		}
		else
		{
			perror("minishell: stat");
			return (1);
		}
	}
	if ((!access(file->name, F_OK)) && (access(file->name, W_OK) == -1))
		return (permission_file_error(file));
	return (0);
}

int	redirection_out(t_file *file)
{
	if (outfile_checker(file))
		return (1);
	if (file->type == FILE_APPEND)
		file->fd = open(file->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		file->fd = open(file->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file->fd == -1)
	{
		perror("minishell: open");
		return (1);
	}
	if (dup2(file->fd, STDOUT_FILENO) == -1)
	{
		close(file->fd);
		perror("minishell: dup2");
		return (1);
	}
	close(file->fd);
	return (0);
}

static int	infile_checker(t_file *file)
{
	if (access(file->name, F_OK) != 0)
		return (no_file_dir(file));
	else if (access(file->name, R_OK) != 0)
		return (permission_file_error(file));
	return (0);
}

int	redirection_in(t_file *file)
{
	if (file->type == FILE_IN)
	{
		if (infile_checker(file))
			return (1);
		file->fd = open(file->name, O_RDONLY);
		if (file->fd == -1)
			return (perror("minishell: open"), 1);
		if (dup2(file->fd, STDIN_FILENO) == -1)
		{
			close(file->fd);
			return (perror("minishell: dup2"), 1);
		}
		close(file->fd);
	}
	else
	{
		if (fill_heredoc_file(file->name))
			return (1);
	}
	return (0);
}
