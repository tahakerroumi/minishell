/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mask_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 11:54:59 by aattak            #+#    #+#             */
/*   Updated: 2024/09/21 11:55:22 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mask_pipes(int *cmd)
{
	int	i;
	int	in_quote;

	i = 0;
	in_quote = 0;
	while (cmd[i])
	{
		if (cmd[i] == MASK_S_QUOTE || cmd[i] == MASK_D_QUOTE)
			in_quote = !in_quote;
		else if (!in_quote && cmd[i] == (int)'|')
			cmd[i] = MASK_PIPE;
		i++;
	}
}
