/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:34:45 by aattak            #+#    #+#             */
/*   Updated: 2024/09/21 11:27:37 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexer(char *command_line)
{
	int		**cmd_args;
	t_token	*token;

	cmd_args = masker(command_line);
	if (!cmd_args)
		return (NULL);
	if (catch_syntax_error(throw_syntax_error(cmd_args), cmd_args))
		return (NULL);
	token = tokenizer(cmd_args);
	if (!token)
	{
		free_int_split(cmd_args);
		return (NULL);
	}
	if (token_iter(token, save_files_original))
	{
		/// hande error here ...
		free_tokens(token, F_ORIGINAL|F_MASK|F_TOKEN);
		return (NULL);
	}
	//print_tokens(token); //////////////////////// delete me 
	return (token);
}
