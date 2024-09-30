/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:33:06 by aattak            #+#    #+#             */
/*   Updated: 2024/09/29 14:12:20 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	null_ambiguous_redirs(t_token *token)
{
	int	spaces;

	if (token->type == TOKEN_IN_FILE || token->type == TOKEN_OUT_FILE
		|| token->type == TOKEN_APPEND_FILE)
	{
		spaces = mask_white_spaces(token->mask);
		if (spaces || token->mask[0] == 0)
		{
			free(token->mask);
			token->mask = NULL;
		}
	}
	return (0);
}

int	set_ignore_me_token(t_token *token)
{
	if (token->type == TOKEN_WORD)
	{
		if (token->mask[0] == 0)
		{
			token->type = TOKEN_IGNORE_ME;
			free(token->mask);
			token->mask = NULL;
		}
	}
	return (0);
}

int	expander(t_token *token)
{
	if (token_iter(token, expand_token))
		return (1);
	token_iter(token, set_ignore_me_token);
	token_iter(token, null_ambiguous_redirs);
	if (token_iter(token, ifs))
		return (1);
	return (0);
}
