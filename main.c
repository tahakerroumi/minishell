/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 00:50:33 by tkerroum          #+#    #+#             */
/*   Updated: 2024/08/31 01:43:24 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialization(char *prompt)
{
	
}

int main(int ac, char **av, char **env)
{
	(void)av;
	char *usrinput;
    if (ac != 1)
    {
        write (2, "the program takes no arguments\n",32);
		return (0);
    }
	while (1)
	{
		usrinput = readline("shymphony@land> ");
		initialization(usrinput);
	}
}