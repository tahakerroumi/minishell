/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:21:34 by aattak            #+#    #+#             */
/*   Updated: 2024/09/29 14:26:05 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_syntax_error	catch_syntax_error(t_syntax_error error, int **args)
{
	if (error)
	{
		free_int_split(args);
		g_root.exit_status = 2;
	}
	if (error == UNEXPECTED_PIPE_ERROR)
		ft_putstr_fd(RED"minishell: syntax error near unexpected token `|'\n"
			RESET, 2);
	else if (error == UNEXPECTED_INPUT_ERROR)
		ft_putstr_fd(RED"minishell: syntax error near unexpected token `<'\n"
			RESET, 2);
	else if (error == UNEXPECTED_OUTPUT_ERROR)
		ft_putstr_fd(RED"minishell: syntax error near unexpected token `>'\n"
			RESET, 2);
	else if (error == UNEXPECTED_HEREDOC_ERROR)
		ft_putstr_fd(RED"minishell: syntax error near unexpected token `<<'\n"
			RESET, 2);
	else if (error == UNEXPECTED_APPEND_ERROR)
		ft_putstr_fd(RED"minishell: syntax error near unexpected token `>>'\n"
			RESET, 2);
	else if (error == UNEXPECTED_NEW_LINE_ERROR)
		ft_putstr_fd(RED"minishell: syntax error near unexpected token "
			"`newline'\n"RESET, 2);
	return (error);
}
