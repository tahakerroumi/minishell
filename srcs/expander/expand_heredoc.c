/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:13:41 by aattak            #+#    #+#             */
/*   Updated: 2024/09/22 13:33:11 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_var_name(char *line)
{
	int		i;
	char	*var_name;

	i = 0;
	if (line[i] == '?')
		return (ft_strdup("?"));
	while (line[i] == '_' || ft_isalnum(line[i]))
		i++;
	var_name = (char *)malloc((i + 1) * sizeof(char));
	if (!var_name)
		return (NULL);
	var_name[i--] = '\0';
	while (i >= 0)
	{
		var_name[i] = line[i];
		i--;
	}
	return (var_name);
}

static int	get_vars_len(char *line)
{
	int		i;
	size_t	len;
	char	*var_name;
	char	*var_value;

	i = 0;
	len = 0;
	while (line[i])
	{
		if (line[i] == '$' && (line[i + 1] == '_' || ft_isalpha(line[i + 1])
				|| line[i + 1] == '?'))
		{
			var_name = extract_var_name(&line[i + 1]);
			if (!var_name)
				return (-1);
			var_value = ft_getenv(var_name);
			len += ft_strlen(var_value);
			i += ft_strlen(var_name);
			free(var_name);
		}
		i++;
	}
	return (len);
}

static int	replace_vars(char *line, char *new_line)
{
	int		i;
	int		j;
	char	*var_name;
	char	*var_value;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '$' && (line[i + 1] == '_' || ft_isalpha(line[i + 1])
				|| line[i + 1] == '?'))
		{
			var_name = extract_var_name(&line[++i]);
			if (!var_name)
				return (1);
			var_value = ft_getenv(var_name);
			ft_memcpy(&new_line[j], var_value, ft_strlen(var_value));
			i += ft_strlen(var_name);
			j += ft_strlen(var_value);
			free(var_name);
		}
		else
			new_line[j++] = line[i++];
	}
	return (0);
}

static char	*reallocate_line(char *line)
{
	int		len;
	int		vars_len;
	char	*new_line;

	vars_len = get_vars_len(line);
	if (vars_len == -1)
		return (NULL);
	len = ft_strlen(line);
	new_line = (char *)ft_calloc(len + vars_len + 1, sizeof(char));
	return (new_line);
}

char	*expand_heredoc(char *line, t_file_type type)
{
	char	*new_line;

	if (type == FILE_HEREDOC)
		return (line);
	new_line = reallocate_line(line);
	if (!new_line)
	{
		free(line);
		return (NULL);
	}
	if (replace_vars(line, new_line))
	{
		free(line);
		free(new_line);
		return (NULL);
	}
	free(line);
	return (new_line);
}
