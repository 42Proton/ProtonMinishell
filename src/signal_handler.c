/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bismail <bismail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:08:44 by bismail           #+#    #+#             */
/*   Updated: 2024/11/28 17:19:40 by bismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void    signal_handler(int signum, siginfo_t *info,void *context)
{
        exit_handler();
}