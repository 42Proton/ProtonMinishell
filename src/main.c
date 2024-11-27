#include <minishell.h>

static void	parse_line(t_minishell *minishell)
{
	execute_inbuilt_command(minishell);
	add_history(minishell->line_read);
	free(minishell->line_read);
}

int	main(void)
{
	t_minishell	*minishell;

	minishell = ft_calloc(1, sizeof(t_minishell));
	if (!minishell)
		exit_handler(minishell, ERR_MALLOC);
	minishell->cwd = malloc(PATH_MAX);
	if (!minishell->cwd)
		exit_handler(minishell, ERR_MALLOC2);
	while (1)
	{
		minishell->line_read = readline("minishell 0x90> ");
		if (!minishell->line_read)
			exit_handler(minishell, NONE);
		if (*minishell->line_read)
			parse_line(minishell);
	}
}