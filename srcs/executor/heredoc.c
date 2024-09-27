/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:18:18 by aattak            #+#    #+#             */
/*   Updated: 2024/09/24 21:37:05 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	random_char(unsigned int i, char *s)
{
	unsigned char *str;

	str = (unsigned char *)s;
	if (!(i % 3) && !(i % 5) && i)
		*str = '_';
	else if (!(i % 3))
		*str = 'A' + ((*str) % 26);
	else if (!(i % 5))
		*str = '0' + ((*str) % 10);
	else
	{
		if (!((*str) % 3) && !((*str) % 5))
			*str = '0' + ((*str) % 10);
		else if (!((*str) % 3))
			*str = 'A' + ((*str) % 26);
		else
			*str = 'a' + ((*str) % 26);
	}
}

/*this function return a file descriptor to the generated file*/
static int	generate_tmp_file(void)
{
	int		fd;
	char	buffer[PRE_LEN + RAND_LEN + SUF_LEN + 1];

	ft_memcpy(buffer, TMP_PREFIX, PRE_LEN);
	fd = open("/dev/random", O_RDONLY);
	read(fd, buffer + PRE_LEN, RAND_LEN);
	close(fd);
	ft_striteri_l(buffer + PRE_LEN, RAND_LEN, random_char);
	ft_memcpy(buffer + PRE_LEN + RAND_LEN, TMP_SUFFIX, SUF_LEN + 1);
	ft_putstr_fd("\nfile_name========\n", 1);
	ft_putstr_fd(buffer, 1);
	ft_putstr_fd("\n=================\n", 1);
	return (0);
}

static int	buffer_to_file(char *buffer)
{
	int	fd;

	fd = open("tmp_heredoc.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
	ft_putstr_fd(GREEN"["RESET, fd);
	ft_putstr_fd(buffer, fd);
	ft_putstr_fd(GREEN"]"RESET, fd);
	ft_putstr_fd("\n========================\n", fd);
	close(fd);
	free(buffer);
	generate_tmp_file();
	return (0);
}

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

static int	fill_heredoc(t_file *file)
{
	char	*line;
	char	*buffer;

	line = NULL;
	buffer = NULL;
	while (file->type == FILE_HEREDOC || file->type == FILE_EX_HEREDOC)
	{
		line = readline("here-doc> ");
		if (g_root.sigint)
			return (free(line), free(buffer), 1);
		if (!line)
			ft_putstr_fd("minishell: warning: here-doc delimited by EOF\n", 2);
		if (line && ft_strcmp(line, file->name))
			buffer = add_line(buffer, line, file->type);
		else
			break ;
		if (!buffer)
			return (1);
	}
	if (file->type == FILE_EX_HEREDOC)
		file->type = FILE_HEREDOC;
	free(line);
	if(file->type == FILE_HEREDOC && buffer_to_file(buffer)) // i must free buffer in the function
		return (1);
	return (0);
}

int	handle_heredocs(t_command *command)
{
	if (file_iter(command->file, fill_heredoc))
		return (1);
	return (0);
}
