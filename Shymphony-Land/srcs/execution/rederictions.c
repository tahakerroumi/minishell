/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rederictions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:53:34 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/19 14:53:48 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	red_fileout(t_file *file)
{
	int		fd;
	struct	stat st;

	if (file->type == FILE_OUT  || file->type == FILE_APPEND)
	{
		if (!stat(file->name, &st) && S_ISDIR(st.st_mode))
			is_dir_error(file);
		else if (access(file->name, X_OK) != 0)
			permission_file_error(file);
		else
		{
			if (file->type == FILE_APPEND)
				fd = open (file->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
			else
				fd = open (file->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd < 0)
				ft_perror("open");
			if (dup2(fd, STDOUT_FILENO) < 0)
			{
				close(fd);
				ft_perror("dup2");
			}
			close(fd);
		}
	}
}

void	red_filein(t_file *file)
{
	int fd;

// HANDLE HEREDOC HERE
	if (file->type == FILE_IN)
	{
		if (access(file->name, F_OK) != 0)
			no_file_dir(file);
		else if (access(file->name, R_OK) != 0)
			permission_file_error(file);
		else
		{
			fd = open(file->name, O_RDONLY);
			if (fd < 0)
				ft_perror("open");
			if (dup2(fd, STDIN_FILENO) < 0)
			{
				close(fd);
				ft_perror("dup2");
			}
			close(fd);
		}
	}
}