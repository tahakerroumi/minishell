/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 12:01:16 by aattak            #+#    #+#             */
/*   Updated: 2024/09/29 13:12:23 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_signals(int flag)
{
	if (flag == IN_PARENT)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (flag == IN_CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}
