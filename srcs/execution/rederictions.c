/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rederictions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:53:34 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/23 12:07:02 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	int	norm_fileout(t_file *file, int child)
{
	struct	stat st;

	if (!stat(file->name, &st) && S_ISDIR(st.st_mode))
	{
		if (is_dir_error(file, child))
			return (1);
	}
    if ((!access(file->name, F_OK)) && (access(file->name, W_OK) == -1))
	{
        if (permission_file_error(file, child))
			return (1);
	}
	return (0);
}

int	rederiction_out(t_file *file, bool child)
{
	if (norm_fileout(file, child))
		return (1);
	else
	{
		if (file->type == FILE_APPEND)
			file->fd = open (file->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			file->fd = open (file->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (file->fd < 0)
			return (ft_perror("open", child));
		if (dup2(file->fd, STDOUT_FILENO) < 0)
		{
			close(file->fd);
			return (ft_perror("dup2", child));
		}
		close(file->fd);
	}
	return (0);
}

static	int	norm_filein(t_file *file, int child)
{
	if (access(file->name, F_OK) != 0)
	{
		if (no_file_dir(file, child))
			return (1);
	}
	else if (access(file->name, R_OK) != 0)
	{
		if (permission_file_error(file, child))
			return (1);	
	}
	return (0);
}

int	rederiction_in(t_file *file, int child)
{
	if (file->type == FILE_IN)
	{
		if (norm_filein(file, child))
			return (1);
		file->fd = open(file->name, O_RDONLY);
		if (file->fd < 0)
			return (ft_perror("open", child));
		if (dup2(file->fd, STDIN_FILENO) < 0)
		{
			close(file->fd);
			return (ft_perror("dup2", child));
		}
		close(file->fd);
	}
	else
	{
		if (dup2(file->fd, STDIN_FILENO) < 0)
		{
			close(file->fd);
			return (ft_perror("dup2", child));
		}
		close(file->fd);
	}
	return (0);
}
