/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:19:39 by aattak            #+#    #+#             */
/*   Updated: 2024/09/25 10:15:53 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(const char *name)
{
	char	*var;
	char	**tmp;

	if (!ft_strcmp(name, "?"))
	if (name && name[0] == '?' && name[1] == '\0')
		return ("1337");//(ft_itoa(g_root.exit_status));
				// normal ft_itoa is bad because it allocate in the heap
				// i need to declare a char array[5] and use it 
				// so i don't need to free after getting the value of $?
	tmp = __environ;
	__environ = g_root.env;
	var = getenv(name);
	__environ = tmp;
	return (var);
}
