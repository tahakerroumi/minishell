/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:54:25 by aattak            #+#    #+#             */
/*   Updated: 2024/09/21 12:09:21 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *head, int f_flag)
{
	t_token	*token;

	while (head)
	{
		token = head;
		head = head->next;
		if ((f_flag & F_MASK) && token->mask)
		{
			free(token->mask);
			token->mask = NULL;
		}
		if ((f_flag & F_CONTENT) && token->content)
		{
			free(token->content);
			token->content = NULL;
		}
		if ((f_flag & F_ORIGINAL) && token->original)
		{
			free(token->original);
			token->original = NULL;
		}
		if (f_flag & F_TOKEN)
			free(token);
	}
}
