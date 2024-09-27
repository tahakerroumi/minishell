
#include "minishell.h"

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
