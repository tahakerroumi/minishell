/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rederictions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:53:34 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/20 14:11:10 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	red_fileout(t_file *file)
{
	struct	stat st;

	if (!stat(file->name, &st) && S_ISDIR(st.st_mode))
		is_dir_error(file);
    if ((!access(file->name, F_OK)) && (access(file->name, W_OK) == -1))
        permission_file_error(file);
	else
	{
		if (file->type == FILE_APPEND)
			file->fd = open (file->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			file->fd = open (file->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (file->fd < 0)
			ft_perror("open");
		if (dup2(file->fd, STDOUT_FILENO) < 0)
		{
			close(file->fd);
			ft_perror("dup2");
		}
		close(file->fd);
	}
}

static	void	norm_filein(t_file *file)
{
	if (access(file->name, F_OK) != 0)
		no_file_dir(file);
	else if (access(file->name, R_OK) != 0)
		permission_file_error(file);
}

void	red_filein(t_file *file)
{
	if (file->type == FILE_IN)
	{
		norm_filein(file);
		file->fd = open(file->name, O_RDONLY);
		if (file->fd < 0)
			ft_perror("open");
		if (dup2(file->fd, STDIN_FILENO) < 0)
		{
			close(file->fd);
			ft_perror("dup2");
		}
		close(file->fd);
	}
	else
	{
		if (dup2(file->fd, STDIN_FILENO) < 0)
		{
			close(file->fd);
			ft_perror("dup2");
		}
		close(file->fd);
	}
}
