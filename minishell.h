/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ta7ino <ta7ino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:42:06 by tkerroum          #+#    #+#             */
/*   Updated: 2024/08/20 13:58:45 by ta7ino           ###   ########.fr       */
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
#include <sys/types.h>
#include <sys/wait.h>
# include "libft/libft.h"

// env
char	**envir_copy(char **env);
int	len_of_env(char **str);

#endif