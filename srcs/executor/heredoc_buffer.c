/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_buffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:18:18 by aattak            #+#    #+#             */
/*   Updated: 2024/09/30 06:03:14 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*add_line(char *buffer, char *line, t_file_type type)
{
	size_t	l_len;
	size_t	b_len;
	char	*new_buffer;

	l_len = 0;
	b_len = 0;
	line = expand_heredoc(line, type);
	if (!line)
		return (free(buffer), NULL);
	l_len = ft_strlen(line);
	b_len = ft_strlen(buffer);
	new_buffer = (char *)ft_calloc(l_len + b_len + 2, sizeof(char));
	if (!new_buffer)
	{
		free(line);
		free(buffer);
		return (NULL);
	}
	ft_memcpy(new_buffer, buffer, b_len);
	free(buffer);
	ft_memcpy(&new_buffer[b_len], line, l_len);
	free(line);
	new_buffer[b_len + l_len] = '\n';
	return (new_buffer);
}

static void	save_buffer(t_file *file, char *buffer)
{
	if (file->type == FILE_HEREDOC)
	{
		free(file->name);
		file->name = buffer;
	}
}

static int	fill_heredoc_buffer(t_file *file)
{
	char	*line;
	char	*buffer;

	line = NULL;
	buffer = NULL;
	while (file->type == FILE_HEREDOC || file->type == FILE_EX_HEREDOC)
	{
		g_root.in_heredoc = 1;
		line = readline("here-doc> ");
		if (g_root.sigint)
			return (free(line), free(buffer), 1);
		if (!line)
			ft_putstr_fd("minishell: warning: here-doc delimited by EOF\n", 2);
		if (!line || !ft_strcmp(line, file->name))
			break ;
		buffer = add_line(buffer, line, file->type);
		if (!buffer)
			return (1);
	}
	if (file->type == FILE_EX_HEREDOC)
		file->type = FILE_HEREDOC;
	free(line);
	save_buffer(file, buffer);
	return (0);
}

int	handle_heredocs(t_command *command)
{
	g_root.sigint = 0;
	if (file_iter(command->file, fill_heredoc_buffer))
	{
		g_root.in_heredoc = 0;
		free_commands(g_root.command, F_ARGV | F_FILE | F_COMMAND);
		return (1);
	}
	g_root.in_heredoc = 0;
	return (0);
}
