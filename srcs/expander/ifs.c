/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:05:32 by aattak            #+#    #+#             */
/*   Updated: 2024/09/21 11:09:28 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	insert_ifs_tokens(t_token *token, t_token *ifs_tokens)
{
	t_token	*tmp_next;

	tmp_next = token->next;
	free(token->mask);
	token->mask = ifs_tokens->mask;
	token->next = ifs_tokens->next;
	free(ifs_tokens);
	while (token->next)
		token = token->next;
	token->next = tmp_next;
}

int	ifs(t_token *token)
{
	int		**split;
	t_token	*ifs_tokens;

	if (token->type == TOKEN_WORD)
	{
		if (mask_white_spaces(token->mask))
		{
			split = split_int_ptr(token->mask, MASK_SPACE);
			if (!split)
				return (1);
			if (!split[0])
			{
				token->mask[0] = 0;
				set_ignore_me_token(token);
				free(split);
				return (0);
			}
			ifs_tokens = tokenizer(split);
			if (!ifs_tokens)
				return (free_int_split(split), 1);
			insert_ifs_tokens(token, ifs_tokens);
		}
	}
	return (0);
}
