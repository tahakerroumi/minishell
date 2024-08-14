/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ta7ino <ta7ino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 08:49:08 by ta7ino            #+#    #+#             */
/*   Updated: 2024/08/13 21:55:39 by ta7ino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	len = ft_strlen((char *)src);
	if (size == 0)
		return (len);
	size--;
	while (i < size && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}

char *ft_strjoin(char* s1, char* s2)
{
    int i = 0;
    int j = 0;
    char *res;

    res = malloc(1 + ft_strlen(s1) + ft_strlen(s2));
    if (!res)
        return (NULL);
    while (s1[i])
    {
        res[i] = s1[i];
        i++;
    }
    while (s2[j])
    {
        res[i] = s2[j];
        j++;
        i++;
    }
    res[i] = '\0';
    return (res);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char *get_path(char **env)
{
    int i = -1;
    while (env[++i])
    {
        if (ft_strncmp(env[i],"PATH",4) == 0)
            return (env[i]);
    }
    return (NULL);
}

static char	**free_if_error(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
}

static int	count_strs(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] == c)
		{
			while (str[i] && str[i] == c)
				i++;
		}
		else
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (count);
}

static size_t	get_strs_size(char const *str, char c)
{
	size_t	i;

	i = 0;
	while (str && str[i] && str[i] != c)
		i++;
	return (i);
}

static char	**start_spliting(char **res, char const *s, char c)
{
	int		s_index;
	int		i;
	size_t	str_size;
	char	*str;

	i = 0;
	s_index = 0;
	while (s && s[i])
	{
		str_size = get_strs_size(s + i, c);
		if (!str_size)
			i++;
		else
		{
			str = malloc(sizeof(char) * (str_size + 1));
			if (!str)
				return (free_if_error(res));
			ft_strlcpy(str, s + i, str_size + 1);
			res[s_index] = str;
			s_index++;
			i += str_size;
		}
	}
	res[s_index] = 0;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;

	if (!s)
		return (NULL);
	res = malloc(sizeof(char *) * (count_strs(s, c) + 1));
	if (!res)
		return (NULL);
	return (start_spliting(res, s, c));
}

int move_path(char *str)
{
    int i = 0;
    while (str[i] && str[i] != ':')
        i++;
    return (i);
}

char **split_path(char *old_path)
{
    int i = move_path(old_path);
    char **new_path = ft_split(old_path + i + 1,':');
    return (new_path);
}

char	*check_exec(char **path,char *command)
{
	int i = 0;
	while (path[i])
	{
		if (!access(command,F_OK))
			return (command);
		char *str = ft_strjoin(path[i], command);
		if (!access(str,F_OK))
			return (str);
		i++;
	}
	return (NULL);
}

void	minishell(char **env, char *prompt)
{
	char *cmd;
    char *envpath = get_path(env);
    char **path = split_path(envpath);
	char **command = ft_split(prompt,' ');
	cmd = ft_strjoin("/",command[0]);
	char *exec = check_exec(path, cmd); // exec first arg;
	if (!exec)
	{
		printf("command not found\n");
		return ;
	}
	int one = execve(exec,command,env);
	if (one == -1)
		printf("command not found\n");
}

int main(int ac, char **av, char **env)
{
	(void)ac;
    (void)av;
	char *prompt;
	while (1)
	{
		prompt = readline("taha's shell:~ ");
		if (!prompt)
			return (0);
		if (ft_strlen(prompt) > 0)
		{
			add_history(prompt);
			minishell(env,prompt);
		}
		free(prompt);
	}
	return (0);
}