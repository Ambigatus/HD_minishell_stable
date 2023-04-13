/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddzuba <ddzuba@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 14:35:54 by hboichuk          #+#    #+#             */
/*   Updated: 2023/04/13 00:31:14 by ddzuba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	event(void)
{
	return (EXIT_SUCCESS);
}

int	sig_checker(t_heredoc heredoc_struct)
{
	if (!heredoc_struct.in_heredoc)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		return (0);
	}
	if (heredoc_struct.in_cmd)
	{
		heredoc_struct.stop_heredoc = 1;
		rl_replace_line("", 0);
		rl_redisplay();
		rl_done = 1;
		return (0);
	}
	return (1);
}

void	sigint_handler(int sig)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void) sig;
}

void	sigquit_handler(int sig)
{
	ft_putstr_fd("Quit: ", STDERR_FILENO);
	ft_putnbr_fd(sig, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	init_signals(t_heredoc heredoc_struct)
{
	rl_event_hook = event;
	if (sig_checker(heredoc_struct) == 1)
		signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
