#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_minishell
{
	char	*prompt;
}	t_minishell;

#endif