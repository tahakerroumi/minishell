/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:57:33 by aattak            #+#    #+#             */
/*   Updated: 2024/09/21 12:06:49 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_files(t_file *head)
{
	t_file	*file;

	while (head)
	{
		file = head;
		head = head->next;
		free(file->name);
		free(file->original);
		free(file);
	}
}
