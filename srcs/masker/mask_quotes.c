/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mask_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 11:53:18 by aattak            #+#    #+#             */
/*   Updated: 2024/09/21 11:54:34 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mask_quotes(int *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		while (cmd[i] && cmd[i] != (int)'\'' && cmd[i] != (int)'\"')
			i++;
		if (cmd[i] == (int)'\'')
		{
			cmd[i++] = MASK_S_QUOTE;
			while (cmd[i] && cmd[i] != (int)'\'')
				i++;
			if (cmd[i] == (int)'\'')
				cmd[i++] = MASK_S_QUOTE;
		}
		if (cmd[i] == (int)'\"')
		{
			cmd[i++] = MASK_D_QUOTE;
			while (cmd[i] && cmd[i] != (int)'\"')
				i++;
			if (cmd[i] == (int)'\"')
				cmd[i++] = MASK_D_QUOTE;
		}
	}
}
