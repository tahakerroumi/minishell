/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 00:43:55 by aattak            #+#    #+#             */
/*   Updated: 2024/09/30 06:20:59 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	random_char(unsigned int i, char *s)
{
	unsigned char	*str;

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

static char	*generate_tmp_file(void)
{
	int			fd;
	static char	buffer[PRE_LEN + RAND_LEN + SUF_LEN + 1];

	ft_memcpy(buffer, TMP_PREFIX, PRE_LEN);
	fd = open("/dev/random", O_RDONLY);
	read(fd, buffer + PRE_LEN, RAND_LEN);
	close(fd);
	ft_striteri_l(buffer + PRE_LEN, RAND_LEN, random_char);
	ft_memcpy(buffer + PRE_LEN + RAND_LEN, TMP_SUFFIX, SUF_LEN + 1);
	return (buffer);
}

int	fill_heredoc_file(char *buffer)
{
	int		fd1;
	int		fd2;
	char	*file_path;

	file_path = generate_tmp_file();
	fd1 = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd1 == -1)
	{
		perror("minishell: open");
		return (1);
	}
	ft_putstr_fd(buffer, fd1);
	fd2 = open(file_path, O_RDONLY);
	close(fd1);
	if (fd2 == -1)
		return (perror("minishell: open"), 1);
	if (dup2(fd2, STDIN_FILENO) == -1)
	{
		close(fd2);
		return (perror("minishell: dup2"), 1);
	}
	close(fd2);
	unlink(file_path);
	return (0);
}
