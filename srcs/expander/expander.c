/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:33:06 by aattak            #+#    #+#             */
/*   Updated: 2024/09/29 14:07:56 by tkerroum         ###   ########.fr       */
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
	// iterate on tokens using the function token_iter(t_token *,
		// void ((*f)(t_token *));
	// extract var names
	// get var values from env if they exist
	// strlen the original string + the var values
	// allocate the new lenght
	// replace $var_name by var value
	if (token_iter(token, expand_token))
		return (1);
		// set IGNORE_ME tokens only for empty WORD tokens
	token_iter(token, set_ignore_me_token);
		// null ambiguous redirections
	token_iter(token, null_ambiguous_redirs);
		// do field splitting using mask_whitespaces
	if (token_iter(token, ifs))
		return (1);
		// print_tokens(token); ////////// delete me
	return (0);
}
