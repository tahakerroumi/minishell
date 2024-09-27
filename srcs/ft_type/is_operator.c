/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_operator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:29:24 by aattak            #+#    #+#             */
/*   Updated: 2024/09/21 11:26:05 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(int c)
{
	if (c == MASK_INPUT || c == MASK_OUTPUT || c == MASK_HEREDOC
		|| c == MASK_APPEND || c == MASK_PIPE)
		return (1);
	return (0);
}
