/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:08:37 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/19 14:34:48 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void    my_pwd(void)
{
    char    buffer[4096];

    if (getcwd(buffer, sizeof(buffer)) != NULL)
    {
        ft_putstr_fd(buffer, 1);
        ft_putstr_fd("\n", 1);
        g_root.exit_status = 0;
    }
    else
    {
        ft_perror("getcwd");
        g_root.exit_status = 1;
    }
}
