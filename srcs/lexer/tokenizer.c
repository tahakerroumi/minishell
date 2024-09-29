/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:16:23 by aattak            #+#    #+#             */
/*   Updated: 2024/09/21 11:40:38 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	assign_token_type(t_token *token, int mask, t_token_type last_type)
{
	if (last_type == TOKEN_INPUT)
		token->type = TOKEN_IN_FILE;
	else if (last_type == TOKEN_OUTPUT)
		token->type = TOKEN_OUT_FILE;
	else if (last_type == TOKEN_HEREDOC)
		token->type = TOKEN_DELIMITER;
	else if (last_type == TOKEN_APPEND)
		token->type = TOKEN_APPEND_FILE;
	else if (mask == MASK_PIPE)
		token->type = TOKEN_PIPE;
	else if (mask == MASK_INPUT)
		token->type = TOKEN_INPUT;
	else if (mask == MASK_OUTPUT)
		token->type = TOKEN_OUTPUT;
	else if (mask == MASK_HEREDOC)
		token->type = TOKEN_HEREDOC;
	else if (mask == MASK_APPEND)
		token->type = TOKEN_APPEND;
	else
		token->type = TOKEN_WORD;
}

static t_token	*create_token(int *arg, t_token *tail)
{
	t_token			*token;
	t_token_type	last_token_type;

	if (!tail)
		last_token_type = 0;
	else
		last_token_type = tail->type;
	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	assign_token_type(token, arg[0], last_token_type);
	token->mask = arg;
	return (token);
}

t_token	*tokenizer(int **cmd_args)
{
	int		i;
	t_token	*head;
	t_token	*tail;
	t_token	*token;

	i = 0;
	head = NULL;
	tail = NULL;
	while (cmd_args[i])
	{
		token = create_token(cmd_args[i], tail);
		if (!token)
		{
			free_tokens(head, F_TOKEN);
			return (NULL);
		}
		if (tail)
			tail->next = token;
		tail = token;
		if (!i)
			head = token;
		i++;
	}
	free(cmd_args);
	return (head);
}

int	save_files_original(t_token *token)
{
	int	i;

	if (token->type == TOKEN_IN_FILE || token->type == TOKEN_OUT_FILE
		|| token->type == TOKEN_APPEND_FILE || token->type == TOKEN_DELIMITER)
	{
		i = 0;
		while (token->mask[i])
			i++;
		token->original = (char *)ft_calloc(i + 1, sizeof(char));
		if (!(token->original))
			return (1);
		i = 0;
		while (token->mask[i])
		{
			token->original[i] = (char)token->mask[i];
			if (token->mask[i] == MASK_S_QUOTE)
				token->original[i] = '\'';
			else if (token->mask[i] == MASK_D_QUOTE)
				token->original[i] = '\"';
			else if (token->mask[i] == MASK_DOLLAR)
				token->original[i] = '$';
			i++;
		}
	}
	return (0);
}
