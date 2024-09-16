/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:53:54 by aattak            #+#    #+#             */
/*   Updated: 2024/09/16 16:08:57 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

# define BOLD "\x1b[1m"
# define GREEN BOLD "\x1b[32m"
# define RED BOLD "\x1b[31m"
# define RESET "\x1b[0m"

# define F_MASK		0b00000001
# define F_CONTENT	0b00000010
# define F_ORIGINAL	0b00000100
# define F_TOKEN	0b00001000

typedef enum	e_mask
{
	MASK_S_QUOTE = 1337,
	MASK_D_QUOTE,
	MASK_DOLLAR,
	MASK_SPACE,
	MASK_PIPE,
	MASK_INPUT,
	MASK_OUTPUT,
	MASK_HEREDOC,
	MASK_APPEND
}	t_mask;

typedef enum	e_syntax_error
{
	NO_SYNTAX_ERROR = 0,
	UNEXPECTED_PIPE_ERROR = 1337,
	UNEXPECTED_INPUT_ERROR,
	UNEXPECTED_OUTPUT_ERROR,
	UNEXPECTED_HEREDOC_ERROR,
	UNEXPECTED_APPEND_ERROR,
	UNEXPECTED_NEW_LINE_ERROR
}	t_syntax_error;

typedef enum	e_token_type
{
	TOKEN_IGNORE_ME = 0,
	TOKEN_COMMAND = 1337,
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_INPUT,
	TOKEN_OUTPUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_IN_FILE,
	TOKEN_OUT_FILE,
	TOKEN_DELIMITER,
	TOKEN_APPEND_FILE
}	t_token_type;

typedef struct	s_token
{
	t_token_type	type;
	int				*mask;
	char			*content;
	char			*original;
	struct s_token	*next;
}	t_token;

typedef enum	e_file_type
{
	FILE_IN = 1337,
	FILE_OUT,
	FILE_HEREDOC,
	FILE_EX_HEREDOC,
	FILE_APPEND,
	FILE_AMBIGUOUS,
	FILE_IGNORE_ME
}	t_file_type;

typedef struct	s_file
{
	t_file_type		type;
	char			*name;
	char			*original;
	int				fd;
	//int				expandable;
	//int				ambiguous;
	struct s_file	*next;
}	t_file;

typedef struct	s_command
{
	char				*path;
	char				**argv;
	// int					max;
	// int					i;
	t_file				*file;
	struct s_command	*next;
}	t_command;

typedef struct	s_root
{
	t_command	*command_line;
	char		**env;
	int			exit_status;
	int			end_loop;
}	t_root;

// tools
char	*ft_strrchr(char *s, int c);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strdup(const char *s1);
char	**ft_split(char const *s, char c);
int		ft_strlen(const char *str);
// void	ft_putstr_fd(char *s, int fd);
void	ft_putstr_fd(char *str, int fd);

// execution
void    executor(t_command *cmd);

extern t_root	g_root;

#endif
