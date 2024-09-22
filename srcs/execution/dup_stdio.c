/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_stdio.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 11:02:17 by ta7ino            #+#    #+#             */
/*   Updated: 2024/09/22 14:43:55 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	save_stdio(t_file *file)
{
	
}

void	handle_io(t_file *head)
{
	t_file *file;

	file = head;
	while (file)
	{
		if (file->type == FILE_AMBIGUOUS)
            ambigious_error(file);
		if (file->type == FILE_IN || file->type == FILE_HEREDOC)
			builtin_rederict(file);
		if (file->type == FILE_OUT || file->type == FILE_APPEND)
			builtin_rederict(file);
		file = file->next;
	}
}
