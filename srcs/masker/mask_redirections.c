/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mask_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 11:57:26 by aattak            #+#    #+#             */
/*   Updated: 2024/09/29 14:38:55 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mask_in_redirs(int *cmd)
{
	int	i;
	int	in_quote;

	i = 0;
	in_quote = 0;
	while (cmd[i])
	{
		if (cmd[i] == MASK_S_QUOTE || cmd[i] == MASK_D_QUOTE)
			in_quote = !in_quote;
		else if (!in_quote && cmd[i] == (int) '<')
		{
			if (cmd[i + 1] == (int) '<')
			{
				cmd[i] = MASK_HEREDOC;
				cmd[i + 1] = MASK_SPACE;
			}
			else
				cmd[i] = MASK_INPUT;
		}
		i++;
	}
}

void	mask_out_redirs(int *cmd)
{
	int	i;
	int	in_quote;

	i = 0;
	in_quote = 0;
	while (cmd[i])
	{
		if (cmd[i] == MASK_S_QUOTE || cmd[i] == MASK_D_QUOTE)
			in_quote = !in_quote;
		else if (!in_quote && cmd[i] == (int) '>')
		{
			if (cmd[i + 1] == (int) '>')
			{
				cmd[i] = MASK_APPEND;
				cmd[i + 1] = MASK_SPACE;
			}
			else
				cmd[i] = MASK_OUTPUT;
		}
		i++;
	}
}
