/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_iterate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:04:59 by aattak            #+#    #+#             */
/*   Updated: 2024/09/21 12:18:40 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_iter(t_token *head, int (*f)(t_token *))
{
	t_token	*token;

	while (head)
	{
		token = head;
		head = head->next;
		if (f)
		{
			if (f(token))
				return (1);
		}
	}
	return (0);
}

int	file_iter(t_file *head, int (*f)(t_file *))
{
	t_file	*file;

	while (head)
	{
		file = head;
		head = head->next;
		if (f)
		{
			if (f(file))
				return (1);
		}
	}
	return (0);
}

int	command_iter(t_command *head, int (*f)(t_command *))
{
	t_command	*command;

	while (head)
	{
		command = head;
		head = head->next;
		if (f)
		{
			if (f(command))
				return (1);
		}
	}
	return (0);
}
