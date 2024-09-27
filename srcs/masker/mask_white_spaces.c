/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mask_white_spaces.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 11:56:51 by aattak            #+#    #+#             */
/*   Updated: 2024/09/21 11:57:00 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mask_white_spaces(int *cmd)
{
	int	i;
	int	spaces;
	int	in_quote;

	i = 0;
	spaces = 0;
	in_quote = 0;
	while (cmd[i])
	{
		if (cmd[i] == MASK_S_QUOTE || cmd[i] == MASK_D_QUOTE)
			in_quote = !in_quote;
		else if (!in_quote && ft_isspace(cmd[i]))
		{
			cmd[i] = MASK_SPACE;
			spaces++;
		}
		i++;
	}
	return (spaces);
}
