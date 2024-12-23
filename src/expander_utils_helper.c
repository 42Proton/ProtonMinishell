/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:06:31 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/23 15:06:55 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*expander_add_tok_helper(char *word, t_tok_expander *tok_exp)
{
	t_split	split_se;
	char	*new_str;
	char	*new_str2;

	split_se = tok_exp->split_se;
	new_str = ft_substr(word, split_se.start, split_se.end - split_se.start);
	if (!new_str)
		return (0);
	if (new_str[0] == '$' && new_str[1] != '?')
	{
		new_str2 = ft_strtrim(new_str, "$");
		if (!new_str2)
			return (0);
		return (new_str2);
	}
	return (new_str);
}
