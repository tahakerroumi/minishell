/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   masker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:34:18 by aattak            #+#    #+#             */
/*   Updated: 2024/09/21 12:00:57 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	*str_to_mask(char *str)
{
	int	i;
	int	len;
	int	*mask;

	if (!str)
		return (NULL);
	if (str[0] == 0)
		return (NULL);
	//////////////////////////////////////////////
	// add_history only non-null command///////////
	add_history(str);
	//////////////////////////////////////////////
	len = ft_strlen(str) + 3;
	mask = (int *)malloc(len * sizeof(int));
	if (!mask)
		return (NULL);
	mask[0] = MASK_SPACE;
	i = 1;
	while (i < len - 2)
	{
		mask[i] = (int)(str[i - 1]);
		i++;
	}
	mask[i++] = MASK_SPACE;
	mask[i] = 0;
	return (mask);
}

static int	*reallocate_cmd(int *cmd)
{
	int	len;
	int	opts;
	int	*new_cmd;

	len = 0;
	opts = 0;
	while (cmd[len])
	{
		if (is_operator(cmd[len]))
			opts += 2;
		len++;
	}
	new_cmd = (int *)malloc((len + opts + 1) * sizeof(int));
	return (new_cmd);
}

static int	*add_white_spaces(int *cmd)
{
	int	i;
	int	j;
	int	*new_cmd;

	new_cmd = reallocate_cmd(cmd);
	if (!new_cmd)
		return (NULL);
	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (is_operator(cmd[i]))
		{
			new_cmd[j++] = MASK_SPACE;
			new_cmd[j++] = cmd[i++];
			new_cmd[j++] = MASK_SPACE;
		}
		else
			new_cmd[j++] = cmd[i++];
	}
	new_cmd[j] = 0;
	free(cmd);
	return (new_cmd);
}

static void	mask_command_line(int *cmd_mask)
{
	mask_quotes(cmd_mask);
	mask_pipes(cmd_mask);
	mask_white_spaces(cmd_mask);
	mask_in_redirs(cmd_mask);
	mask_out_redirs(cmd_mask);
	mask_dollar_signs(cmd_mask);
}

int	**masker(char *command_line)
{
	int	*cmd_mask;
	int	**cmd_args;

	cmd_mask = str_to_mask(command_line); ////////////// char to int
	free(command_line);
	if (!cmd_mask)
		return (NULL);
	mask_command_line(cmd_mask); ////////////////////// mask command line
	// print_mask(cmd_mask);//
	cmd_mask = add_white_spaces(cmd_mask); //////////////// add whitespaces
	if (!cmd_mask)
		return (NULL);
	// print_mask(cmd_mask);//
	cmd_args = split_int_ptr(cmd_mask, MASK_SPACE); /////// split cmd args
	free(cmd_mask);
	if (!cmd_args)
		return (NULL);
	if (!cmd_args[0])
	{
		free(cmd_args);
		return (NULL);
	}
	unmask_dollar_signs(cmd_args); ////////////////// unmask dollar signs
	// print_cmd_args(cmd_args);
	return (cmd_args);
}
