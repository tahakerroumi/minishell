/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:11:42 by aattak            #+#    #+#             */
/*   Updated: 2024/09/20 21:05:55 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_var_name(int *mask)
{
	int		i;
	char	*var_name;

	i = 0;
	if (mask[i] == (int)'?')
		return (ft_strdup("?"));
	while (mask[i] == (int)'_' || ft_isalnum(mask[i]))
		i++;
	var_name = (char *)malloc((i + 1) * sizeof(char));
	if (!var_name)
		return (NULL);
	var_name[i--] = '\0';
	while (i >= 0)
	{
		var_name[i] = (char)mask[i];
		i--;
	}
	return (var_name);
}

static int	get_vars_len(int *mask) /// if the function failed it return -1
{
	int		i;
	size_t	len;
	char	*var_name;
	char	*var_value;

	i = 0;
	len = 0;
	while (mask[i])
	{
		if (mask[i] == MASK_DOLLAR)
		{
			// extract var name
			var_name = extract_var_name(&mask[i + 1]);
			if (!var_name)
				return (-1);
			// get var value
			var_value = ft_getenv(var_name);
			// get var value len
			len += ft_strlen(var_value);
			// skip var name
			i += ft_strlen(var_name);
			// Print vars for test
			printf("\n[%s] = ", var_name);
			if (var_value)
				printf("[%s]\n", var_value);
			else
				printf("[NULL]\n");
			// free allocs
			free(var_name);
			// free(var_value); /// this is a dumb invalid free 
			// cuz its just a pointer to the value in the env.
		}
		i++; /// this also skip the dollar sign
	}
	return (len);
}

static int	replace_vars(int *mask, int *new_mask)
{
	int		i;
	int		j;
	char	*var_name;
	char	*var_value;

	i = 0;
	j = 0;
	while (mask[i])
	{
		if (mask[i] == MASK_DOLLAR)
		{
			var_name = extract_var_name(&mask[++i]);
			if (!var_name)
				return (1);
			var_value = ft_getenv(var_name);
			strcpy_to_int(&new_mask[j], var_value);
			i += ft_strlen(var_name);
			j += ft_strlen(var_value);
			free(var_name);
		}
		else
			new_mask[j++] = mask[i++];
	}
	return (0);
}

static int	*reallocate_token_mask(int *mask)
{
	int	len;
	int	vars_len;
	int	*new_mask;

	vars_len = get_vars_len(mask);
	if (vars_len == -1)
		return (NULL);
	//printf("\nvars_len = %d\n\n", vars_len); /// test
	len = 0;
	while (mask[len])
		len++;
	//printf("old mask len = %d  vars len = %d \n", len, vars_len);
	new_mask = (int *)ft_calloc(len + vars_len + 1, sizeof(int));
	return (new_mask);
}

int	expand_token(t_token *token)
{
	int	*new_mask;

	new_mask = reallocate_token_mask(token->mask);
	if (!new_mask)
		return (1);
	// then get vars values and replace them in the mask
	if (replace_vars(token->mask, new_mask))
	{
		free(new_mask);
		return (1);
	}
	/// free the old mask and replace it by the new one
	free(token->mask);
	token->mask = new_mask;
	return (0);
}
