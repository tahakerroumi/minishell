/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:55:54 by aattak            #+#    #+#             */
/*   Updated: 2024/09/21 11:33:42 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_syntax_error	check_pipe_syntax(int **args, size_t i)
{
	if (!args[i] && i != 1)
		return (UNEXPECTED_NEW_LINE_ERROR);
	if (i == 1 || args[i][0] == MASK_PIPE)
		return (UNEXPECTED_PIPE_ERROR);
	return (NO_SYNTAX_ERROR);
}

static t_syntax_error	check_redirections_syntax(int **args, size_t i)
{
	if (!args[i])
		return (UNEXPECTED_NEW_LINE_ERROR);
	if (args[i][0] == MASK_PIPE)
		return (UNEXPECTED_PIPE_ERROR);
	if (args[i][0] == MASK_INPUT)
		return (UNEXPECTED_INPUT_ERROR);
	if (args[i][0] == MASK_OUTPUT)
		return (UNEXPECTED_OUTPUT_ERROR);
	if (args[i][0] == MASK_HEREDOC)
		return (UNEXPECTED_HEREDOC_ERROR);
	if (args[i][0] == MASK_APPEND)
		return (UNEXPECTED_APPEND_ERROR);
	return (NO_SYNTAX_ERROR);
}

static t_syntax_error	check_operator_syntax(int **args, size_t i)
{
	t_syntax_error	error;

	error = NO_SYNTAX_ERROR;
	if (args[i][0] == MASK_PIPE)
		error = check_pipe_syntax(args, i + 1);
	else if (is_operator(args[i][0]))
		error = check_redirections_syntax(args, i + 1);
	return (error);
}

static t_syntax_error	check_unclosed_quotes(int *args)
{
	size_t	i;
	int		in_s_quote;
	int		in_d_quote;

	i = 0;
	in_s_quote = 0;
	in_d_quote = 0;
	while (args[i])
	{
		while (args[i] && args[i] != MASK_S_QUOTE && args[i] != MASK_D_QUOTE)
			i++;
		if (!args[i])
			break ;
		if (args[i] == MASK_S_QUOTE)
			in_s_quote = !in_s_quote;
		else
			in_d_quote = !in_d_quote;
		i++;
	}
	if (in_s_quote || in_d_quote)
		return (UNEXPECTED_NEW_LINE_ERROR);
	return (NO_SYNTAX_ERROR);
}

t_syntax_error	throw_syntax_error(int **args)
{
	size_t			i;
	t_syntax_error	error;

	i = 0;
	error = NO_SYNTAX_ERROR;
	while (args[i])
	{
		if (is_operator(args[i][0]))
			error = check_operator_syntax(args, i);
		else if (!args[i + 1])
			error = check_unclosed_quotes(args[i]);
		if (error != NO_SYNTAX_ERROR)
			return (error);
		i++;
	}
	return (error);
}

t_syntax_error	catch_syntax_error(t_syntax_error error, int **args)
{
	if (error)
	{
		free_int_split(args);
		// i have also to set the exit status $? to 2
	}
	if (error == UNEXPECTED_PIPE_ERROR)
		ft_putstr_fd(RED "bash: syntax error near unexpected token `|'\n" RESET,
			2);
	else if (error == UNEXPECTED_INPUT_ERROR)
		ft_putstr_fd(RED "bash: syntax error near unexpected token `<'\n" RESET,
			2);
	else if (error == UNEXPECTED_OUTPUT_ERROR)
		ft_putstr_fd(RED "bash: syntax error near unexpected token `>'\n" RESET,
			2);
	else if (error == UNEXPECTED_HEREDOC_ERROR)
		ft_putstr_fd(RED "bash: syntax error near unexpected token `<<'\n" RESET,
			2);
	else if (error == UNEXPECTED_APPEND_ERROR)
		ft_putstr_fd(RED "bash: syntax error near unexpected token `>>'\n" RESET,
			2);
	else if (error == UNEXPECTED_NEW_LINE_ERROR)
		ft_putstr_fd(RED "bash: syntax error near unexpected token `newline'\n" RESET,
			2);
	return (error);
}
