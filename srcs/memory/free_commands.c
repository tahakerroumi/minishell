/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:58:35 by aattak            #+#    #+#             */
/*   Updated: 2024/09/21 12:06:58 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_commands(t_command *head, int f_flag)
{
	t_command	*command;

	while (head)
	{
		command = head;
		head = head->next;
		if (f_flag & F_PATH)
		{
			free(command->path);
			command->path = NULL;
		}
		if (f_flag & F_ARGV)
		{
			free_string_array(command->argv);
			command->argv = NULL;
		}
		if (f_flag & F_FILE)
		{
			free_files(command->file);
			command->file = NULL;
		}
		if (f_flag & F_COMMAND)
			free(command);
	}
}
