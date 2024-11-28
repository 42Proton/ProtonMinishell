#include <minishell.h>

static void	parse_line(t_minishell *minishell)
{
	execute_inbuilt_command(minishell);
	add_history(minishell->line_read);
	free(minishell->line_read);
}

static int	parse_env_data(char *data, t_env *env)
{
	int		i;
	int		j;

	i = 0;
	while (data[i] != '=')
		i++;
	i++;
	env->name = malloc(i * sizeof(char));
	if (!env->name)
		return (0);
	ft_strlcpy(env->name, data, i);
	j = i;
	while (data[j])
		j++;
	env->data = malloc(((j - i) + 1) * sizeof(char));
	if (!env->data)
	{
		free(env->name);
		return (0);
	}
	ft_strlcpy(env->data, data + i, j + 1);
	return (1);
}

static void	prep_minishell_env(t_minishell *minishell, char **ev)
{
	t_env	*env;
	t_list	*lst;

	while (*ev)
	{
		env = malloc(sizeof(t_env));
		if (!env)
			exit_handler(minishell, ERR_MALLOC2);
		parse_env_data(*ev, env);
		lst = ft_lstnew(env);
		if (!lst)
		{
			free(env);
			exit_handler(minishell, ERR_MALLOC2);
		}
		if (!minishell->env_lst)
			minishell->env_lst = lst;
		else
			ft_lstadd_back(&minishell->env_lst, lst);
		ev++;
	}
}

static t_minishell	*minishell_prep(void)
{
	t_minishell	*minishell;
	extern char	**environ;

	minishell = ft_calloc(1, sizeof(t_minishell));
	if (!minishell)
		exit_handler(minishell, ERR_MALLOC);
	minishell->cwd = malloc(PATH_MAX);
	if (!minishell->cwd)
		exit_handler(minishell, ERR_MALLOC2);
	if (*environ)
		prep_minishell_env(minishell, environ);
	return (minishell);
}

int	main()
{
	t_minishell	*minishell;
	struct sigaction sa;
	sa.sa_flags = SA_SIGINFO
	sa.sa_sigaction = &signal_handler;

	sigaction(SIGINT,&sa, NULL);
	minishell = minishell_prep();
	while (1)
	{
		minishell->line_read = readline("\e[33mminishell 0x90\e[0m> ");
		if (!minishell->line_read)
			exit_handler(minishell, NONE);
		if (*minishell->line_read)
			parse_line(minishell);
	}
}