/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mask_dollar_signs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 11:55:52 by aattak            #+#    #+#             */
/*   Updated: 2024/09/29 14:37:59 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unmask_heredoc(int **args, int i)
{
	size_t	j;

	j = 0;
	while (args[i + 1][j])
	{
		if (args[i + 1][j] == MASK_DOLLAR)
			args[i + 1][j] = (int) '$';
		j++;
	}
}

void	unmask_dollar_signs(int **args)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == MASK_HEREDOC && args[i + 1])
			unmask_heredoc(args, i);
		else if (!is_operator(args[i][0]))
		{
			j = 0;
			while (args[i][j])
			{
				if (args[i][j] == MASK_DOLLAR && !ft_isalpha(args[i][j + 1])
					&& args[i][j + 1] != (int) '_'
					&& args[i][j + 1] != (int) '?')
					args[i][j] = (int) '$';
				j++;
			}
		}
		i++;
	}
}

void	mask_dollar_signs(int *cmd)
{
	int	i;
	int	in_quote;

	i = 0;
	in_quote = 0;
	while (cmd[i])
	{
		if (cmd[i] == MASK_S_QUOTE)
			in_quote = !in_quote;
		else if (!in_quote && cmd[i] == (int) '$')
			cmd[i] = MASK_DOLLAR;
		i++;
	}
}
