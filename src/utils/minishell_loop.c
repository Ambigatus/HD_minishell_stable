/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddzuba <ddzuba@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 16:06:58 by hboichuk          #+#    #+#             */
/*   Updated: 2023/04/02 20:46:53 by ddzuba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	reset(t_global *global)
{
	ft_simple_cmdsclear(&global->simple_cmds);
	free(global->args);
	if (global->pid)
		free(global->pid);
	free_arr(global->paths);
	init_global_struct(global);
	global->reset = true;
	run_minishell(global);
	return (1);
}

int	prepare_executor(t_global *global)
{
	signal(SIGQUIT, sigquit_handler);
	heredoc_struct.in_cmd = 1;
	if (global->pipes == 0)
		single_cmd(global->simple_cmds, global);
	else
	{
		global->pid = ft_calloc(sizeof(int), global->pipes + 2);
		if (!global->pid)
			return (ft_error(1, global));
		executor(global);
	}
	heredoc_struct.in_cmd = 0;
	return (EXIT_SUCCESS);
}
