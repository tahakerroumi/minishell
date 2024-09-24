/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:50:56 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/24 21:00:11 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int save_stdio(t_file *file)
{
    int in;
    int out;

    out = dup(STDOUT_FILENO);
    in = dup(STDIN_FILENO);
}