/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:08:37 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/24 21:07:51 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    builtin_pwd(void)
{
    char    buffer[4096];

    if (getcwd(buffer, sizeof(buffer)) != NULL)
    {
        ft_putstr_fd(buffer, 1);
        ft_putstr_fd("\n", 1);
        return (0);
    }
    else
        return (ft_perror("getcwd", 0));
}

