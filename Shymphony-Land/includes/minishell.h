/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:53:54 by aattak            #+#    #+#             */
/*   Updated: 2024/09/18 21:57:58 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

# define BOLD		"\x1b[1m"
# define GREEN BOLD	"\x1b[32m"
# define RED BOLD	"\x1b[31m"
# define BLUE BOLD	"\x1b[94m"
# define RESET		"\x1b[0m"

# define F_MASK		0b000000001
# define F_CONTENT	0b000000010
# define F_ORIGINAL	0b000000100
# define F_TOKEN	0b000001000

# define F_PATH		0b000010000
# define F_ARGV		0b000100000
# define F_FILE		0b001000000
# define F_COMMAND	0b010000000

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
	int				fd;
	char			*name;
	char			*original;
	struct s_file	*next;
}	t_file;

typedef struct	s_command
{
	char				*path;
	char				**argv;
	t_file				*file;
	int					pipefd[3];
	pid_t				pid;
	struct s_command	*next;
}	t_command;

typedef struct	s_root
{
	//t_command	*command_line;
	char	**env;
	int		sigint;
	int		exit_status;
	int		end_loop;
}	t_root;

extern t_root	g_root;

// execution
void    execution(t_command *cmd);
int		waiting(t_command *cmd);
void	ft_pipe(int *fd);
pid_t	ft_fork();
void	ft_execve(t_command *cmd);
void	ft_perror(char *msg);

// tools
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s1);
void	ft_putstr_fd(char *str, int fd);
int		ft_strlen(char *str);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strcpy(char *dest, const char *src);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isalpha(int c);
void	free_argv(char **av);


// parsing
char	*ft_getenv(const char *name);

#endif
