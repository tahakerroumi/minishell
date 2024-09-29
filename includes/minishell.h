/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:53:54 by aattak            #+#    #+#             */
/*   Updated: 2024/09/29 15:17:29 by tkerroum         ###   ########.fr       */
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
# include <stdbool.h>

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

# define TMP_PREFIX	"/tmp/miniH3ll-tmp."
# define PRE_LEN	18
# define TMP_SUFFIX	".here-doc"
# define SUF_LEN	9
# define RAND_LEN	16

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
	t_command		*command;
	char			**env;
	size_t			env_size;
	size_t			env_count;
	int				sigint;
	unsigned int	exit_status;
	int				end_loop;
}	t_root;

extern t_root	g_root;

/*execution*/
int		execution(t_command *head);
int		start_executing(t_command *cmd);
int		create_pipes(t_command *cmd, int *fd);
int		is_builtin(t_command *cmd);
int		handle_files(t_file *head);
int		ft_perror(char *msg, int child);
int		ft_execve(t_command *cmd);
int		waiting(t_command *cmd);
int		execute_builtin(t_command *cmd);
int		permission_file_error(t_file *file);
int		is_dir_error(t_file *file);
int		no_file_dir(t_file *file);
int		ambigious_error(t_file *file);
int		rederiction_in(t_file *file);
int		rederiction_out(t_file *file);
void	child_routine(t_command *cmd);
void	init_signals(void);
void	handle_pipes(int *pipefd);
void	execute(t_command *cmd);
void	exec_command(t_command *cmd);
void	exec(char **path, t_command *cmd);
void	exec_path(t_command *cmd);
void    no_such_f_d(t_command *cmd);
void    is_dir_cmd(t_command *cmd);
void    no_permission(t_command *cmd);
void    not_found(t_command *cmd);
int		too_many_args(char **cmd);
char	*ft_getcwd(void);

/*tools*/
char	**ft_split(char const *s, char c);
char	*ft_strcpy(char *dest, const char *src);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strchr(const char *s, int c);
int		ft_isalpha(int c);
void	free_string_array(char **av);
int		ft_isdigit(int c);
char	*ft_strtrim(char  *s1, char  *set);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_getenv(const char *name);

/*builtin*/
int		execute_builtin(t_command *cmd);
int		builtin_pwd(char **argv);
int		builtin_echo(char **argv);
int		builtin_exit(char **argv);
int		builtin_env(char **argv);
int		builtin_cd(char **argv);

/*Debugging Functions*/
void			print_mask(int *cmd_mask);
void			print_cmd_args(int **cmd);
void			print_tokens(t_token *token);
void			print_files(t_file *file);
void			print_commands(t_command *command);

/*MiniShell Loop*/
void			minishell_loop();

/*ENVIRONMENT Functions*/
void			init_env(void);
char			*ft_getenv(const char *name);
int				is_valid_env_key(char *key);
int				realloc_env(void);
int				ft_putenv(char *var);
int				ft_unsetenv(char *key);

/*Masker*/
int				**masker(char *command_line);
void			mask_quotes(int *cmd);
void			mask_pipes(int *cmd);
int				mask_white_spaces(int *cmd);
void			mask_in_redirs(int *cmd);
void			mask_out_redirs(int *cmd);
void			mask_dollar_signs(int *cmd);
void			unmask_dollar_signs(int **args);

/*Lexer*/
t_token			*lexer(char *command_line);
t_syntax_error	throw_syntax_error(int **args);
t_syntax_error	catch_syntax_error(t_syntax_error error, int **args);
t_token			*tokenizer(int **cmd_args);
int				save_files_original(t_token *token);

/*Parser*/
t_command 		*parser(char *command_line);
t_command		*form_commands(t_token *token);

/*Expander*/
int				expander(t_token *token);
int				expand_token(t_token *token);
char			*expand_heredoc(char *line, t_file_type type);
int				set_ignore_me_token(t_token *token);
int				null_ambiguous_redirs(t_token *token);
int				ifs(t_token *token);

/*Memory*/
void			*ft_calloc(size_t count, size_t size);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			free_tokens(t_token *head, int f_flag);
void			free_commands(t_command *head, int f_flag);
void			free_files(t_file *head);
void			free_string_array(char **av);
void			free_int_split(int **split);

/*Built-ins*/
int				builtin_export(char **argv);
int				builtin_unset(char **argv);

/*Executor*/
int				handle_heredocs(t_command *command);

/*Utilities*/
int				token_iter(t_token *head, int (*f)(t_token *));
int				file_iter(t_file *head, int (*f)(t_file *));
int				command_iter(t_command *head, int (*f)(t_command *));

/*ft_string*/
void			ft_putstr_fd(char *str, int fd);
char			*ft_strchr(const char *s, int c);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strdup(const char *s1);
int				ft_strlen(char *str);
void			ft_striteri_l(char *str, size_t len,
					void (*f)(unsigned int, char *));
int				**split_int_ptr(int *ptr, int sep);
void			strcpy_to_int(int *dest, const char *src);

/*ft_type*/
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isspace(int c);
int				is_operator(int c);

#endif
