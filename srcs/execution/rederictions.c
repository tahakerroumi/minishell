/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rederictions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:53:34 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/25 00:43:14 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	outfile_checker(t_file *file)
{
	struct stat	st;

	if (!stat(file->name, &st) && S_ISDIR(st.st_mode))
		return (is_dir_error(file));
	if ((!access(file->name, F_OK)) && (access(file->name, W_OK) == -1))
		return (permission_file_error(file));
	else
		return (0);
}

int	rederiction_out(t_file *file)
{
	if (outfile_checker(file))
		return (1);
	if (file->type == FILE_APPEND)
		file->fd = open(file->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		file->fd = open(file->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file->fd < 0)
		ft_perror("open", 1);
	if (dup2(file->fd, STDOUT_FILENO) < 0)
	{
		close(file->fd);
		ft_perror("dup2", 1);
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
	else
		return (0);
}

int	rederiction_in(t_file *file)
{
	if (file->type == FILE_IN)
	{
		if (infile_checker(file))
			return (1);
		file->fd = open(file->name, O_RDONLY);
		if (file->fd < 0)
			return (ft_perror("open", 1));
		if (dup2(file->fd, STDIN_FILENO) < 0)
		{
			close(file->fd);
			return (ft_perror("dup2", 1));
		}
		close(file->fd);
	}
	else
	{
		if (dup2(file->fd, STDIN_FILENO) < 0)
		{
			close(file->fd);
			return (ft_perror("dup2", 1));
		}
		close(file->fd);
	}
	return (0);
}
