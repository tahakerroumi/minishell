/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkerroum <tkerroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:40:03 by aattak            #+#    #+#             */
/*   Updated: 2024/09/24 20:52:47 by tkerroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_calloc(size_t count, size_t size);

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	h;

	i = 0;
	h = (char)c;
	while (s[i] && s[i] != h)
		i++;
	if (s[i] == h)
		return ((char *)s + i);
	return (NULL);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

void	strcpy_to_int(int *dest, const char *src)
{
	int	i;

	if (src)
	{
		i = 0;
		while (src[i])
		{
			dest[i] = (int)src[i];
			i++;
		}
		dest[i] = 0;
	}
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*ptr;

	ptr = (char *)malloc((ft_strlen((char *)s1) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

void	ft_putstr_fd(char *str, int fd)
{
	if (str)
		write(fd, str, ft_strlen(str));
}

int	*str_to_mask(char *str)
{
	int	i;
	int	len;
	int	*mask;

	if (!str)
		return (NULL);
	if (str[0] == 0)
		return (NULL);
	//////////////////////////////////////////////
	//add_history only non-null command///////////
	add_history(str);
	//////////////////////////////////////////////
	len = ft_strlen(str) + 3;
	mask = (int *)malloc(len * sizeof(int));
	if (!mask)
		return NULL;
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

void	mask_quotes(int *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		while (cmd[i] && cmd[i] != (int)'\'' && cmd[i] != (int)'\"')
			i++;
		if (cmd[i] == (int)'\'')
		{
			cmd[i++] = MASK_S_QUOTE;
			while (cmd[i] && cmd[i] != (int)'\'')
				i++;
			if (cmd[i] == (int)'\'')
				cmd[i++] = MASK_S_QUOTE;
		}
		if (cmd[i] == (int)'\"')
		{
			cmd[i++] = MASK_D_QUOTE;
			while (cmd[i] && cmd[i] != (int)'\"')
				i++;
			if (cmd[i] == (int)'\"')
				cmd[i++] = MASK_D_QUOTE;
		}
	}
}

void	mask_pipes(int *cmd)
{
	int	i;
	int	in_quote;

	i = 0;
	in_quote = 0;
	while (cmd[i])
	{
		if (cmd[i] == MASK_S_QUOTE || cmd[i] == MASK_D_QUOTE)
			in_quote = !in_quote;
		else if (!in_quote && cmd[i] == (int)'|')
			cmd[i] = MASK_PIPE;
		i++;
	}
}

void	mask_dollar_signs(int *cmd)
{
	int	i;
	int in_quote;

	i = 0;
	in_quote = 0;
	while (cmd[i])
	{
		if (cmd[i] == MASK_S_QUOTE)
			in_quote = !in_quote;
		else if (!in_quote && cmd[i] == (int)'$')
			cmd[i] = MASK_DOLLAR;
		i++;
	}
}

int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	mask_white_spaces(int *cmd)
{
	int	i;
	int	spaces;
	int	in_quote;

	i = 0;
	spaces = 0;
	in_quote = 0;
	while (cmd[i])
	{
		if (cmd[i] == MASK_S_QUOTE || cmd[i] == MASK_D_QUOTE)
			in_quote = !in_quote;
		else if (!in_quote && ft_isspace(cmd[i]))
		{
			cmd[i] = MASK_SPACE;
			spaces++;
		}
		i++;
	}
	return (spaces);
}

void	mask_in_redirs(int *cmd)
{
	int	i;
	int	in_quote;

	i = 0;
	in_quote = 0;
	while (cmd[i])
	{
		if (cmd[i] == MASK_S_QUOTE || cmd[i] == MASK_D_QUOTE)
			in_quote = !in_quote;
		else if (!in_quote && cmd[i] == (int)'<')
		{
			if (cmd[i + 1] == (int)'<')
			{
				cmd[i] = MASK_HEREDOC;
				cmd[i + 1] = MASK_SPACE;
			}
			else
				cmd[i] = MASK_INPUT;
		}
		i++;
	}
}

void	mask_out_redirs(int *cmd)
{
	int	i;
	int	in_quote;

	i = 0;
	in_quote = 0;
	while (cmd[i])
	{
		if (cmd[i] == MASK_S_QUOTE || cmd[i] == MASK_D_QUOTE)
			in_quote = !in_quote;
		else if (!in_quote && cmd[i] == (int)'>')
		{
			if (cmd[i + 1] == (int)'>')
			{
				cmd[i] = MASK_APPEND;
				cmd[i + 1] = MASK_SPACE;
			}
			else
				cmd[i] = MASK_OUTPUT;
		}
		i++;
	}
}

void	mask_command_line(int *cmd_mask)
{
	mask_quotes(cmd_mask);
	mask_pipes(cmd_mask);
	mask_white_spaces(cmd_mask);
	mask_in_redirs(cmd_mask);
	mask_out_redirs(cmd_mask);
	mask_dollar_signs(cmd_mask);
}	

void	print_mask(int *cmd_mask)
{
	int	i;

	i = 0;
	//printf("\n");
	if (!cmd_mask)
	{
		printf(GREEN"NULL"RESET);
		return ;
	}
	while (cmd_mask[i])
	{
		switch (cmd_mask[i])
		{
			case MASK_S_QUOTE:
				printf("%s\'%s", GREEN, RESET);
				break ;
			case MASK_D_QUOTE:
				printf("%s\"%s", GREEN, RESET);
				break ;
			case MASK_PIPE:
				printf("%s|%s", GREEN, RESET);
				break ;
			case MASK_DOLLAR:
				printf("%s$%s", GREEN, RESET);
				break ;
			case MASK_SPACE:
				printf("%s_%s", GREEN, RESET);
				break ;
			case MASK_INPUT:
				printf("%s<%s", GREEN, RESET);
				break ;
			case MASK_HEREDOC:
				printf("%s<<%s", GREEN, RESET);
				break ;
			case MASK_OUTPUT:
				printf("%s>%s", GREEN, RESET);
				break ;
			case MASK_APPEND:
				printf("%s>>%s", GREEN, RESET);
				break ;
			default:
				printf("%c", (char)cmd_mask[i]);
		}
		i++;
	}
	//printf("\n\n");
}

int is_operator(int c)
{
	if (c == MASK_INPUT || c == MASK_OUTPUT || c == MASK_HEREDOC
		|| c == MASK_APPEND || c == MASK_PIPE)
		return (1);
	return (0);
}

int	*reallocate_cmd(int *cmd)
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

int	*add_white_spaces(int *cmd)
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

void	print_cmd_args(int **cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i])
	{
		printf("\n");
		print_mask(cmd[i++]);
		printf("\n");
	}
}

void	unmask_dollar_signs(int **args)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == MASK_HEREDOC && args[i + 1])
		{
			j = 0;
			while (args[i + 1][j])
			{
				if (args[i + 1][j] == MASK_DOLLAR)
					args[i + 1][j] = (int)'$';
				j++;
			}
		}
		else if (!is_operator(args[i][0]))
		{
			j = 0;
			while (args[i][j])
			{
				if (args[i][j] == MASK_DOLLAR && !ft_isalpha(args[i][j + 1])
					&& args[i][j + 1] != (int)'_' && args[i][j + 1] != (int)'?')
					args[i][j] = (int)'$';
				j++;
			}
		}
		i++;
	}
}

int	**split_int_ptr(int *ptr, int sep);
void	free_int_split(int **split);

t_syntax_error	check_pipe_syntax(int **args, size_t i)
{
	if (!args[i] && i != 1)
		return (UNEXPECTED_NEW_LINE_ERROR);
	if (i == 1 || args[i][0] == MASK_PIPE)
		return (UNEXPECTED_PIPE_ERROR);
	return (NO_SYNTAX_ERROR);
}

t_syntax_error	check_redirections_syntax(int **args, size_t i)
{
	if (!args[i])
		return (UNEXPECTED_NEW_LINE_ERROR);
	if (args[i][0] == MASK_PIPE)
		return (UNEXPECTED_PIPE_ERROR);
	if (args[i][0] == MASK_INPUT)
		return (UNEXPECTED_INPUT_ERROR);
	if (args[i][0] == MASK_OUTPUT)
		return (UNEXPECTED_OUTPUT_ERROR);
	if (args[i][0] == MASK_HEREDOC)
		return (UNEXPECTED_HEREDOC_ERROR);
	if (args[i][0] == MASK_APPEND)
		return (UNEXPECTED_APPEND_ERROR);
	return (NO_SYNTAX_ERROR);
}

t_syntax_error	check_operator_syntax(int **args, size_t i)
{
	t_syntax_error	error;

	error = NO_SYNTAX_ERROR;
	if (args[i][0] == MASK_PIPE)
		error = check_pipe_syntax(args, i + 1);
	else if (is_operator(args[i][0]))
		error = check_redirections_syntax(args, i + 1);
	return (error);
}

t_syntax_error check_unclosed_quotes(int *args)
{
	size_t	i;
	int		in_s_quote;
	int		in_d_quote;

	i = 0;
	in_s_quote = 0;
	in_d_quote = 0;
	while (args[i])
	{
		while (args[i] && args[i] != MASK_S_QUOTE && args[i] != MASK_D_QUOTE)
			i++;
		if (!args[i])
			break;
		if (args[i] == MASK_S_QUOTE)
			in_s_quote = !in_s_quote;
		else
			in_d_quote = !in_d_quote;
		i++;
	}
	if (in_s_quote || in_d_quote)
		return (UNEXPECTED_NEW_LINE_ERROR);
	return (NO_SYNTAX_ERROR);
}

t_syntax_error	throw_syntax_error(int **args)
{
	size_t				i;
	t_syntax_error		error;

	i = 0;
	error = NO_SYNTAX_ERROR;
	while (args[i])
	{
		if (is_operator(args[i][0]))
			error = check_operator_syntax(args, i);
		else if (!args[i + 1])
			error = check_unclosed_quotes(args[i]);
		if (error != NO_SYNTAX_ERROR)
			return (error);
		i++;
	}
	return (error);
}

t_syntax_error catch_syntax_error(t_syntax_error error, int **args)
{
	if (error)
	{
		free_int_split(args);
		//i have also to set the exit status $? to 2
	}
	if (error == UNEXPECTED_PIPE_ERROR)
		ft_putstr_fd(RED"bash: syntax error near unexpected token `|'\n"
			RESET, 2);
	else if (error == UNEXPECTED_INPUT_ERROR)
		ft_putstr_fd(RED"bash: syntax error near unexpected token `<'\n"
			RESET, 2);
	else if (error == UNEXPECTED_OUTPUT_ERROR)
		ft_putstr_fd(RED"bash: syntax error near unexpected token `>'\n"
			RESET, 2);
	else if (error == UNEXPECTED_HEREDOC_ERROR)
		ft_putstr_fd(RED"bash: syntax error near unexpected token `<<'\n"
			RESET, 2);
	else if (error == UNEXPECTED_APPEND_ERROR)
		ft_putstr_fd(RED"bash: syntax error near unexpected token `>>'\n"
			RESET, 2);
	else if (error == UNEXPECTED_NEW_LINE_ERROR)
		ft_putstr_fd(RED"bash: syntax error near unexpected token `newline'\n"
			RESET, 2);
	return (error);
}

void	assign_token_type(t_token *token, int mask, t_token_type last_type)
{
	if (last_type == TOKEN_INPUT)
		token->type = TOKEN_IN_FILE;
	else if (last_type == TOKEN_OUTPUT)
		token->type = TOKEN_OUT_FILE;
	else if (last_type == TOKEN_HEREDOC)
		token->type = TOKEN_DELIMITER;
	else if (last_type == TOKEN_APPEND)
		token->type = TOKEN_APPEND_FILE;
	else if (mask == MASK_PIPE)
		token->type = TOKEN_PIPE;
	else if (mask == MASK_INPUT)
		token->type = TOKEN_INPUT;
	else if (mask == MASK_OUTPUT)
		token->type = TOKEN_OUTPUT;
	else if (mask == MASK_HEREDOC)
		token->type = TOKEN_HEREDOC;
	else if (mask == MASK_APPEND)
		token->type = TOKEN_APPEND;
	else
		token->type = TOKEN_WORD;
}

t_token	*create_token(int *arg, t_token *tail)
{
	t_token			*token;
	t_token_type	last_token_type;

	if (!tail)
		last_token_type = 0;
	else
		last_token_type = tail->type;
	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	assign_token_type(token, arg[0], last_token_type);
	token->mask = arg;
	return (token);
}

void	free_token_mask(t_token *token) //// useless now
{
	free(token->mask);
}

void	free_token_content(t_token *token) //// useless now
{
	free(token->content);
}

void	__free_tokens__(t_token *head, void (*del)(t_token *)) //// useless now
{
	t_token	*token;

	while (head)
	{
		token = head;
		head = head->next;
		if (del)
			del(token);
		free(token);
	}
}

void	free_tokens(t_token *head, int f_flag)
{
	t_token	*token;

	while (head)
	{
		token = head;
		head = head->next;
		if ((f_flag & F_MASK) && token->mask)
		{
			free(token->mask);
			token->mask = NULL;
		}
		if ((f_flag & F_CONTENT) && token->content)
		{
			free(token->content);
			token->content = NULL;
		}
		if ((f_flag & F_ORIGINAL) && token->original)
		{
			free(token->original);
			token->original = NULL;
		}
		if (f_flag & F_TOKEN)
			free(token);
	}
}

t_token	*tokenizer(int **cmd_args)
{
	int		i;
	t_token	*head;
	t_token	*tail;
	t_token	*token;

	i = 0;
	head = NULL;
	tail = NULL;
	while (cmd_args[i])
	{
		token = create_token(cmd_args[i], tail);
		if (!token)
		{
			free_tokens(head, F_TOKEN);
			return (NULL);
		}
		if (tail)
			tail->next = token;
		tail = token;
		if (!i)
			head = token;
		i++;
	}
	free(cmd_args);
	return (head);
}

void	print_tokens(t_token *token)
{
	printf("\n\n\nBEGIN------------------------------------\n");
	while (token)
	{
		//printf("\n------------------TOKEN------------------\n");
		switch (token->type)
		{
			case TOKEN_WORD:
				printf("\n%s[TOKEN_WORD] : %s", RED, RESET);
				break ;
			case TOKEN_PIPE:
				printf("\n%s[TOKEN_PIPE] : %s", RED, RESET);
				break ;
			case TOKEN_INPUT:
				printf("\n%s[TOKEN_INPUT] : %s", RED, RESET);
				break ;
			case TOKEN_OUTPUT:
				printf("\n%s[TOKEN_OUTPUT] : %s", RED, RESET);
				break ;
			case TOKEN_HEREDOC:
				printf("\n%s[TOKEN_HEREDOC] : %s", RED, RESET);
				break ;
			case TOKEN_APPEND:
				printf("\n%s[TOKEN_APPEND] : %s", RED, RESET);
				break ;
			case TOKEN_IN_FILE:
				printf("\n%s[TOKEN_IN_FILE] : %s", RED, RESET);
				break ;
			case TOKEN_OUT_FILE:
				printf("\n%s[TOKEN_OUT_FILE] : %s", RED, RESET);
				break ;
			case TOKEN_DELIMITER:
				printf("\n%s[TOKEN_DELIMITER] : %s", RED, RESET);
				break ;
			case TOKEN_APPEND_FILE:
				printf("\n%s[TOKEN_APPEND_FILE] : %s", RED, RESET);
				break ;
			case TOKEN_COMMAND:
				printf("\n%s[TOKEN_COMMAND] : %s", RED, RESET);
				break ;
			case TOKEN_IGNORE_ME:
				printf("\n%s[TOKEN_IGNORE_ME] : %s", RED, RESET);
				break ;
		}
		if (!(token->mask) && !(token->content) && !(token->original))
			printf(RED" [NULL]\n"RESET);
		else
			printf("\n");
		if (token->mask)
		{
			printf(GREEN"\t[MASK]\t\t= ["RESET);
			print_mask(token->mask);
			printf(GREEN"]\n"RESET);
		}
		if (token->content)
			printf("%s\t[CONTENT]\t= [%s%s%s]%s\n",GREEN, RESET, token->content, GREEN, RESET);
		else if (token->original)
			printf(GREEN"\t[CONTENT]\t= [NULL]\n"RESET);
		if (token->original)
		{
			printf("%s\t[ORIGINAL]\t= [%s%s%s]%s\n",GREEN, RESET, token->original, GREEN, RESET);
		}
		token = token->next;
	}
	printf("\nEND--------------------------------------\n");
	printf("\n\n");
}

int	**masker(char *command_line)
{
	int		*cmd_mask;
	int		**cmd_args;

	cmd_mask = str_to_mask(command_line); ////////////// char to int
	free(command_line);
	if (!cmd_mask)
		return (NULL);

	mask_command_line(cmd_mask); ////////////////////// mask command line
	//print_mask(cmd_mask);//

	cmd_mask = add_white_spaces(cmd_mask); //////////////// add whitespaces
	if (!cmd_mask)
		return (NULL);
	//print_mask(cmd_mask);//

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
	//print_cmd_args(cmd_args);
	return (cmd_args);
}

int	token_iter(t_token *head, int (*f)(t_token *))
{
	t_token	*token;

	while (head)
	{
		token = head;
		head = head->next;
		if (f)
		{
			if (f(token))
				return (1);
		}
	}
	return (0);
}

char	*ft_getenv(const char *name)
{
	//__environ = g_root.env; // to bypass the lines and colums problem discussed with unes
							  // when setting or unsetting an env variable.
	if (ft_strcmp(name, "?"))
		return (getenv(name));
	printf("\n\n%d\n\n", g_root.exit_status); ////
	return ("1337");//(ft_itoa(g_root.exit_status));
			// normal ft_itoa is bad because it allocate in the heap
			// i need to declare a char array[5] and use it 
			// so i don't need to free after getting the value of $?
}

char	*extract_var_name(int *mask)
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

//int	*get_int_env()
//{
//}

int	get_vars_len(int *mask) /// if the function failed it return -1
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
			if (var_value)
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

int	*reallocate_token_mask(int *mask)
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

int	replace_vars(int *mask, int *new_mask)
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

int	expand_token_vars(t_token *token)
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

void	insert_ifs_tokens(t_token *token, t_token *ifs_tokens)
{
	t_token	*tmp_next;

	tmp_next = token->next;
	free(token->mask);
	token->mask = ifs_tokens->mask;
	token->next = ifs_tokens->next;
	free(ifs_tokens);
	while (token->next)
		token = token->next;
	token->next = tmp_next;
}

int	null_ambiguous_redirs(t_token *token)
{
	int	spaces;

	if (token->type == TOKEN_IN_FILE || token->type == TOKEN_OUT_FILE ||
		token->type == TOKEN_APPEND_FILE)
	{
		spaces = mask_white_spaces(token->mask);
		if (spaces || token->mask[0] == 0)
		{
			free(token->mask);
			token->mask = NULL;
		}
	}
	return (0);
}

int	set_ignore_me_token(t_token *token)
{
	if (token->type == TOKEN_WORD)
	{
		if (token->mask[0] == 0)
		{
			token->type = TOKEN_IGNORE_ME;
			free(token->mask);
			token->mask = NULL;
		}
	}
	return (0);
}

int	ifs(t_token *token)
{
	int		**split;
	t_token	*ifs_tokens;

	if (token->type == TOKEN_WORD)
	{
		if (mask_white_spaces(token->mask))
		{
			split = split_int_ptr(token->mask, MASK_SPACE);
			if (!split)
				return (1);
			if (!split[0])
			{
				token->mask[0] = 0;
				set_ignore_me_token(token);
				free(split);
				return (0);
			}
			ifs_tokens = tokenizer(split);
			if (!ifs_tokens)
				return (free_int_split(split), 1);
			insert_ifs_tokens(token, ifs_tokens);
		}
	}
	return (0);
}

int	expander(t_token *token)
{
	// iterate on tokens using the function token_iter(t_token *, void (*f)(t_token *))
	// extract var names
	// get var values from env if they exist
	// strlen the original string + the var values
	// allocate the new lenght
	// replace $var_name by var value
	if (token_iter(token, expand_token_vars))
		return (1);
	// set IGNORE_ME tokens only for empty WORD tokens
	token_iter(token, set_ignore_me_token);
	// null ambiguous redirections
	token_iter(token, null_ambiguous_redirs);
	// do field splitting using mask_whitespaces
	if (token_iter(token, ifs))
		return (1);
	//print_tokens(token); ////////// delete me
	return (0);
}

int	save_files_original(t_token *token)
{
	int	i;

	if (token->type == TOKEN_IN_FILE || token->type == TOKEN_OUT_FILE ||
		token->type == TOKEN_APPEND_FILE || token->type == TOKEN_DELIMITER)
	{
		i = 0;
		while (token->mask[i])
			i++;
		token->original = (char *)ft_calloc(i + 1, sizeof(char));
		if (!(token->original))
			return (1);
		i = 0;
		while (token->mask[i])
		{
			token->original[i] = (char)token->mask[i];
			if (token->mask[i] == MASK_S_QUOTE)
				token->original[i] = '\'';
			else if (token->mask[i] == MASK_D_QUOTE)
				token->original[i] = '\"';
			else if (token->mask[i] == MASK_DOLLAR)
				token->original[i] = '$';
			i++;
		}
	}
	return (0);
}

t_token	*lexer(char *command_line)
{
	int		**cmd_args;
	t_token	*token;

	cmd_args = masker(command_line);
	if (!cmd_args)
		return (NULL);
	if (catch_syntax_error(throw_syntax_error(cmd_args), cmd_args))
		return (NULL);
	token = tokenizer(cmd_args);
	if (!token)
	{
		free_int_split(cmd_args);
		return (NULL);
	}
	if (token_iter(token, save_files_original))
	{
		/// hande error here ...
		free_tokens(token, F_ORIGINAL|F_MASK|F_TOKEN);
		return (NULL);
	}
	//print_tokens(token); //////////////////////// delete me 
	return (token);
}

int	mask_to_content(t_token *token)
{
	int	i;
	int	j;

	if ((token->type == TOKEN_WORD || token->type == TOKEN_IN_FILE
		|| token->type == TOKEN_OUT_FILE || token->type == TOKEN_APPEND_FILE
		|| token->type == TOKEN_DELIMITER) && token->mask)
	{
		i = 0;
		while (token->mask[i])
			i++;
		token->content = (char *)ft_calloc(i + 1, sizeof(char));
		if (!(token->content))
			return (1);
		i = 0;
		j = 0;
		while (token->mask[i])
		{
			if (token->mask[i] <= 127 && token->mask[i] >= -128)
				token->content[j++] = (char)(token->mask[i]);
			i++;
		}
	}
	return (0);
}

void	print_files(t_file *file)
{
	while (file)
	{
		switch (file->type)
		{
			case FILE_IN:
				printf(GREEN"\n\t[FILE IN] : "RESET);
				break ;
			case FILE_OUT:
				printf(GREEN"\n\t[FILE OUT] : "RESET);
				break ;
			case FILE_HEREDOC:
				printf(GREEN"\n\t[FILE HEREDOC] : "RESET);
				break ;
			case FILE_EX_HEREDOC:
				printf(GREEN"\n\t[FILE EX HEREDOC] : "RESET);
				break ;
			case FILE_APPEND:
				printf(GREEN"\n\t[FILE APPEND] : "RESET);
				break ;
			case FILE_AMBIGUOUS:
				printf(GREEN"\n\t[FILE AMBIGUOUS] : "RESET);
				break ;
			case FILE_IGNORE_ME:
				printf(GREEN"\n\t[FILE IGNORE ME] : "RESET);
				break ;
		}
		if (file->fd)
			printf(BLUE"\n\t   [FD]       : ["RESET"%d"BLUE"] "RESET, file->fd);
		else
			printf(BLUE"\n\t   [FD]       : [NULL] "RESET);
		if (file->name)
			printf(BLUE"\n\t   [NAME]     : ["RESET"%s"BLUE"] "RESET, file->name);
		else
			printf(BLUE"\n\t   [NAME]     : [NULL] "RESET);
		if (file->original)
			printf(BLUE"\n\t   [ORIGINAL] : ["RESET"%s"BLUE"] \n"RESET, file->original);
		else
			printf(BLUE"\n\t   [ORIGINAL] : [NULL] \n"RESET);
		file = file->next;
	}
}

void	print_commands(t_command *command)
{
	int	i;
	int	ac;

	i = 0;
	while (command)
	{
		printf("\n[COMMAND %d] : ---------------------------------\n", i);
		if (command->path)
			printf(RED"\n[PATH]  : ["RESET"%s"RED"] \n"RESET, command->path);
		else
			printf(RED"\n[PATH]  : [NULL] \n"RESET);
		printf(RED"\n[ARGV]  : "RESET);
		ac = 0;
		if (!(command->argv[0]))
			printf(RED"[NULL]"RESET);
		while (command->argv[ac])
			printf(RED"["RESET"%s"RED"] "RESET, command->argv[ac++]);
		printf("\n");
		if (command->file)
			printf(RED"\n[FILES] : "RESET);
		else
			printf(RED"\n[FILES] : [NULL]"RESET);
		print_files(command->file);
		printf("\n\n-----------------------------------------------\n");
		command = command->next;
		i++;
	}
}

void	free_string_array(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		free(av[i++]);
	free(av);
}

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

void	free_commands(t_command *head, int f_flag)
{
	t_command	*command;

	while (head)
	{
		command = head;
		head = head->next;
		if (f_flag & F_PATH)
		{
			free(command->path);
			command->path = NULL;
		}
		if (f_flag & F_ARGV)
		{
			free_string_array(command->argv);
			command->argv = NULL;
		}
		if (f_flag & F_FILE)
		{
			free_files(command->file);
			command->file = NULL;
		}
		if (f_flag & F_COMMAND)
			free(command);
	}
}

int	get_argc(t_token *token)
{
	int	argc;

	argc = 0;
	while (token)
	{
		if (token->type == TOKEN_WORD)
			argc++;
		token = token->next;
	}
	return (argc);
}

void	fill_file_data(t_file *file, t_token *token)
{
	if (token->type == TOKEN_DELIMITER && (ft_strchr(token->original, '\'')
		|| ft_strchr(token->original, '"')))
		file->type = FILE_EX_HEREDOC;
	else if (token->type == TOKEN_DELIMITER)
		file->type = FILE_HEREDOC;
	if (!(token->content))
		file->type = FILE_AMBIGUOUS;
	else
	{
		if (token->type == TOKEN_IN_FILE)
			file->type = FILE_IN;
		else if (token->type == TOKEN_OUT_FILE)
			file->type = FILE_OUT;
		else if (token->type == TOKEN_APPEND_FILE)
			file->type = FILE_APPEND;
		free(token->original);
		token->original = NULL;
	}
	file->name = token->content;
	file->original = token->original;
	token->original = NULL;
}

t_command	*form_commands(t_token *token)
{
	int			i;
	int			argc;
	t_command	*head;
	t_command	*tail;
	t_command	*command;
	t_file		*file;
	t_file		*file_tail;

	head = NULL;
	tail = NULL;
	while (token)
	{
		command = (t_command *)ft_calloc(1, sizeof(t_command));
		if (!command)
		{
			free_commands(command, F_PATH | F_ARGV | F_FILE | F_COMMAND);
			return(NULL);
		}
		if (tail)
			tail->next = command;
		tail = command;
		if (!head)
			head = command;
		argc = get_argc(token); // TOKEN_WORD only
		command->argv = (char **)ft_calloc(argc + 1, sizeof(char *));
		if (!(command->argv))
		{
			free_commands(command, F_PATH | F_ARGV | F_FILE | F_COMMAND);
			return(NULL);
		}
		i = 0;
		file_tail = NULL;
		while (token && token->type != TOKEN_PIPE)
		{
			// assign token to command
			if (token->type == TOKEN_WORD)
				command->argv[i++] = token->content;
			else if (token->type == TOKEN_INPUT || token->type == TOKEN_OUTPUT
				|| token->type == TOKEN_HEREDOC || token->type == TOKEN_APPEND)
			{
				/// handle files
				file = (t_file *)ft_calloc(1, sizeof(t_file));
				if (!file)
				{
					free_commands(command, F_PATH | F_ARGV | F_FILE | F_COMMAND);
					return(NULL);
				}
				if (file_tail)
					file_tail->next = file;
				file_tail = file;
				if (!(command->file))
					command->file = file;
				fill_file_data(file, token->next);
				token = token->next; // i can remove this line if i got norm errors
			}
			token->content = NULL;
			token = token->next;
		}
		if (token && token->type == TOKEN_PIPE)
			token = token->next;
	}
	return (head);
}

t_command *parser(char *command_line)
{
	t_token		*token;
	t_command	*command;

	token = lexer(command_line);
	if (!token)
		return (NULL);
	if (expander(token))
	{
		free_tokens(token, F_TOKEN | F_MASK | F_ORIGINAL);
		return (NULL);
	}
	if (token_iter(token, mask_to_content))
	{
		free_tokens(token, F_TOKEN | F_MASK | F_CONTENT | F_ORIGINAL);
		return (NULL);
	}
	free_tokens(token, F_MASK);
	command = form_commands(token);
	if (!command)
	{
		free_tokens(token, F_TOKEN | F_ORIGINAL | F_CONTENT);
		return (NULL);
	}
	free_tokens(token, F_TOKEN);
	return (command);
}

// void read_int(int sig)
// {
// 	(void)sig;
// 	write(1, "\n\nCATCH SIG\n\n", 13);
// 	rl_callback_handler_install(NULL, NULL);
// 	rl_cleanup_after_signal();
// 	//rl_done = 1;
// }

// int	read_int_wrapper(void)
// {
// 	read_int(SIGINT);
// 	return (0);
// }

void	minishell_loop()
{
	char		*command_line;
	t_command	*command;

	g_root.end_loop = 0; /////////// delete me
	// signal(SIGINT, read_int);
	// rl_signal_event_hook = read_int_wrapper;
	while (!g_root.end_loop)
	{
		printf("\n\n"); ////////////////////// delete me
		command_line = readline(GREEN"Shymphony@Land ~> "RESET);
		if (!command_line) ////////// means the user clicked on ctrl+d
			g_root.end_loop = 1;

		///////////////////////////////////////////////////////////////////
		//if (command_line && command_line[0] == '^') ///////////////////////
		//	g_root.end_loop = 1; //////////////////////////////////////////
		///////////////////////////////////////////////////////////////////

		command = parser(command_line);
		if (!command)
			continue ;

		///// handle heredocs after forming commands
		// command_iter(t_command *command, handle_heredocs(t_command *command);

		/////////////////////////////////////////////////////////
		print_commands(command); ///////////////////

		if (execution(command))
		{
			// cleanup all of it
			continue;
		}

		free_commands(command, F_PATH | F_ARGV | F_FILE | F_COMMAND);//
		/////////////////////////////////////////////////////////
	}
}

t_root	g_root;

int	main(int ac, char **av)
{
	(void)av;
	if (ac == 1)
	{
		//minishell_init(); // init shell variables like IFS
		//env_init();
		g_root.env = __environ;
		minishell_loop();
		rl_clear_history();
		printf("exit\n");
		////////////////////////////////close(3);/////////////////
		return (g_root.exit_status);
	}
	ft_putstr_fd(RED"minishell accepts no arguments\n"RESET, 2);
	return (1);
}

