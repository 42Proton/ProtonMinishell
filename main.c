#include <minishell.h>

int	main(void)
{
	t_minishell	*minishell;

	minishell = malloc(sizeof(t_minishell));
	if (!minishell)
		return (EXIT_FAILURE);
	minishell->prompt = "minishell 0x90> ";
	readline(minishell->prompt);
}