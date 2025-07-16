/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:16:39 by anfichet          #+#    #+#             */
/*   Updated: 2024/06/24 19:16:40 by anfichet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	init_hook(void)
{
	return (1);
}

void	init_signal(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	rl_event_hook = init_hook;
	g_signal = 0;
}

void	sig_handler(int signal)
{
	g_signal = signal;
	if (g_signal == SIGINT)
		rl_done = 1;
}
