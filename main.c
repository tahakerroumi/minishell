/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ta7ino <ta7ino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 08:49:08 by ta7ino            #+#    #+#             */
/*   Updated: 2024/08/09 11:15:32 by ta7ino           ###   ########.fr       */
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

int main(int ac, char **env)
{
    // int i = -1;
    char *av[] = {"ls","-l",NULL};
    char *path = "/usr/bin/ls ";
    char *str = readline("taha/>:~ ");
    // char *res = ft_strjoin(path,str);
    execve(path,av,env);
}