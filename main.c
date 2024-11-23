#include <minishell.h>

void	print_error(int error)
{
	if (error == ERR_MALLOC)
		ft_putstr_fd("Error: malloc failed\n", 2);
}

void	exit_handler(t_minishell *minishell, int error)
{
	print_error(error);
	if (error > ERR_MALLOC)
	{
		rl_clear_history();
		free(minishell->cwd);
		free(minishell->line_read);
		free(minishell);
	}
	if (error != NONE)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

void	parse_line(t_minishell *minishell)
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