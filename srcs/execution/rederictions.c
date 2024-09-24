/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rederictions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:53:34 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/24 20:52:22 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	outfile_checker(t_file *file)
{
	struct	stat st;

	if (!stat(file->name, &st) && S_ISDIR(st.st_mode))
		is_dir_error(file);
    if ((!access(file->name, F_OK)) && (access(file->name, W_OK) == -1))
        permission_file_error(file);
}

void	rederiction_out(t_file *file)
{
	outfile_checker(file);
	if (file->type == FILE_APPEND)
		file->fd = open (file->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		file->fd = open (file->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file->fd < 0)
	{
		perror("open");
		exit(1);
	}
	if (dup2(file->fd, STDOUT_FILENO) < 0)
	{
		close(file->fd);
		perror("dup2");
		exit(1);
	}
	close(file->fd);
}

static	void	infile_checker(t_file *file)
{
	if (access(file->name, F_OK) != 0)
		no_file_dir(file);
	else if (access(file->name, R_OK) != 0)
		permission_file_error(file);
}

void	rederiction_in(t_file *file)
{
	if (file->type == FILE_IN)
	{
		infile_checker(file);
		file->fd = open(file->name, O_RDONLY);
		if (file->fd < 0)
		{
			perror("open");
			exit(1);
		}
		if (dup2(file->fd, STDIN_FILENO) < 0)
		{
			close(file->fd);
			perror("dup2");
			exit(1);
		}
		close(file->fd);
	}
	else
	{
		if (dup2(file->fd, STDIN_FILENO) < 0)
		{
			close(file->fd);
			perror("dup2");
			exit(1);
		}
		close(file->fd);
	}
}
