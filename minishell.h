/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 00:59:31 by tkerroum          #+#    #+#             */
/*   Updated: 2024/09/07 03:40:15 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include "libft/libft.h"
char	**envir_copy(char **env);
int	len_of_env(char **str);


typedef enum s_type
{
    CMD_SIMPLE,
    CMD_PIPE,
    CMD_REDIRECT_OUT,
    CMD_APPEND,
    CMD_HEREDOC
}           e_type;

typedef struct s_command
{
    e_type  type;              // Type of the command or operation (using integer constants)
    char    *cmd_name;        // Command name (e.g., "ls")
    char    **args;           // Arguments (e.g., ["-la", "/home"])
    char    *filename;        // Filename for redirections (e.g., "input.txt")
    char    *heredoc_delim;   // Delimiter for heredoc (e.g., "EOF")
    struct  s_command *left;  // Left subtree (e.g., left side of a pipe)
    struct  s_command *right; // Right subtree (e.g., right side of a pipe)
}              t_command;

#endif