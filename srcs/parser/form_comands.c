/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_comands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:46:55 by aattak            #+#    #+#             */
/*   Updated: 2024/09/21 12:17:38 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_argc(t_token *token)
{
	int	argc;

	argc = 0;
	while (token)
	{
		if (token->type == TOKEN_WORD)
			argc++;
		token = token->next;
	}
	return (argc);
}

static void	fill_file_data(t_file *file, t_token *token)
{
	if (token->type == TOKEN_DELIMITER && (ft_strchr(token->original, '\'')
		|| ft_strchr(token->original, '"')))
		file->type = FILE_HEREDOC;
	else if (token->type == TOKEN_DELIMITER)
		file->type = FILE_EX_HEREDOC;
	if (!(token->content))
		file->type = FILE_AMBIGUOUS;
	else
	{
		if (token->type == TOKEN_IN_FILE)
			file->type = FILE_IN;
		else if (token->type == TOKEN_OUT_FILE)
			file->type = FILE_OUT;
		else if (token->type == TOKEN_APPEND_FILE)
			file->type = FILE_APPEND;
		free(token->original);
		token->original = NULL;
	}
	file->name = token->content;
	file->original = token->original;
	token->original = NULL;
}

t_command	*form_commands(t_token *token)
{
	int			i;
	int			argc;
	t_command	*head;
	t_command	*tail;
	t_command	*command;
	t_file		*file;
	t_file		*file_tail;

	head = NULL;
	tail = NULL;
	while (token)
	{
		command = (t_command *)ft_calloc(1, sizeof(t_command));
		if (!command)
		{
			free_commands(command, F_PATH | F_ARGV | F_FILE | F_COMMAND);
			return(NULL);
		}
		if (tail)
			tail->next = command;
		tail = command;
		if (!head)
			head = command;
		argc = get_argc(token); // TOKEN_WORD only
		command->argv = (char **)ft_calloc(argc + 1, sizeof(char *));
		if (!(command->argv))
		{
			free_commands(command, F_PATH | F_ARGV | F_FILE | F_COMMAND);
			return(NULL);
		}
		i = 0;
		file_tail = NULL;
		while (token && token->type != TOKEN_PIPE)
		{
			// assign token to command
			if (token->type == TOKEN_WORD)
				command->argv[i++] = token->content;
			else if (token->type == TOKEN_INPUT || token->type == TOKEN_OUTPUT
				|| token->type == TOKEN_HEREDOC || token->type == TOKEN_APPEND)
			{
				/// handle files
				file = (t_file *)ft_calloc(1, sizeof(t_file));
				if (!file)
				{
					free_commands(command, F_PATH | F_ARGV | F_FILE | F_COMMAND);
					return(NULL);
				}
				if (file_tail)
					file_tail->next = file;
				file_tail = file;
				if (!(command->file))
					command->file = file;
				fill_file_data(file, token->next);
				token = token->next; // i can remove this line if i got norm errors
			}
			token->content = NULL;
			token = token->next;
		}
		if (token && token->type == TOKEN_PIPE)
			token = token->next;
	}
	return (head);
}
