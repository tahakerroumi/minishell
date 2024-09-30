/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_comands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:46:55 by aattak            #+#    #+#             */
/*   Updated: 2024/09/29 14:42:08 by aattak           ###   ########.fr       */
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

static int	create_command(t_token *token, t_command **tail)
{
	int			argc;
	t_command	*command;

	command = (t_command *)ft_calloc(1, sizeof(t_command));
	if (!command)
	{
		free_commands(g_root.command, F_PATH | F_ARGV | F_FILE | F_COMMAND);
		return (1);
	}
	if (*tail)
		(*tail)->next = command;
	*tail = command;
	if (!g_root.command)
		g_root.command = command;
	argc = get_argc(token);
	command->argv = (char **)ft_calloc(argc + 1, sizeof(char *));
	if (!(command->argv))
	{
		free_commands(g_root.command, F_PATH | F_ARGV | F_FILE | F_COMMAND);
		return (1);
	}
	return (0);
}

static int	fill_command_data(t_token *token, t_command *cmd, t_file **tail,
	int *argc)
{
	t_file		*file;

	if (token->type == TOKEN_WORD)
		cmd->argv[(*argc)++] = token->content;
	else if (token->type == TOKEN_INPUT || token->type == TOKEN_OUTPUT
		|| token->type == TOKEN_HEREDOC || token->type == TOKEN_APPEND)
	{
		file = (t_file *)ft_calloc(1, sizeof(t_file));
		if (!file)
		{
			free_commands(g_root.command, F_PATH | F_ARGV | F_FILE | F_COMMAND);
			return (1);
		}
		if (*tail)
			(*tail)->next = file;
		*tail = file;
		if (!(cmd->file))
			cmd->file = file;
		fill_file_data(file, token->next);
	}
	token->content = NULL;
	return (0);
}

int	form_commands(t_token *token)
{
	int			argc;
	t_command	*cmds_tail;
	t_file		*files_tail;

	cmds_tail = NULL;
	while (token)
	{
		if (create_command(token, &cmds_tail))
			return (1);
		argc = 0;
		files_tail = NULL;
		while (token && token->type != TOKEN_PIPE)
		{
			if (fill_command_data(token, cmds_tail, &files_tail, &argc))
				return (1);
			token = token->next;
		}
		if (token && token->type == TOKEN_PIPE)
			token = token->next;
	}
	return (0);
}
