/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:45:04 by aattak            #+#    #+#             */
/*   Updated: 2024/09/21 12:12:28 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	mask_to_content(t_token *token)
{
	int	i;
	int	j;

	if ((token->type == TOKEN_WORD || token->type == TOKEN_IN_FILE
			|| token->type == TOKEN_OUT_FILE || token->type == TOKEN_APPEND_FILE
			|| token->type == TOKEN_DELIMITER) && token->mask)
	{
		i = 0;
		while (token->mask[i])
			i++;
		token->content = (char *)ft_calloc(i + 1, sizeof(char));
		if (!(token->content))
			return (1);
		i = 0;
		j = 0;
		while (token->mask[i])
		{
			if (token->mask[i] <= 127 && token->mask[i] >= -128)
				token->content[j++] = (char)(token->mask[i]);
			i++;
		}
	}
	return (0);
}

t_command	*parser(char *command_line)
{
	t_token		*token;
	t_command	*command;

	token = lexer(command_line);
	if (!token)
		return (NULL);
	if (expander(token))
	{
		free_tokens(token, F_TOKEN | F_MASK | F_ORIGINAL);
		return (NULL);
	}
	if (token_iter(token, mask_to_content))
	{
		free_tokens(token, F_TOKEN | F_MASK | F_CONTENT | F_ORIGINAL);
		return (NULL);
	}
	free_tokens(token, F_MASK);
	command = form_commands(token);
	if (!command)
	{
		free_tokens(token, F_TOKEN | F_ORIGINAL | F_CONTENT);
		return (NULL);
	}
	free_tokens(token, F_TOKEN);
	return (command);
}
