/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddzuba <ddzuba@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:04:02 by hboichuk          #+#    #+#             */
/*   Updated: 2023/04/13 00:21:07 by ddzuba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	run_minishell(t_global *global);

int	run_minishell(t_global *global)
{
	global->args = readline("minishell:");
	lexer(global);
	parser(global);
	prepare_executor(global);
	reset(global);
	return (1);
}

int	init_global_struct(t_global *global)
{
	global->simple_cmds = NULL;
	global->lexer_list = NULL;
	global->reset = false;
	global->pid = NULL;
	global->heredoc = false;
	global->heredoc_struct.stop_heredoc = 0;
	global->heredoc_struct.in_cmd = 0;
	global->heredoc_struct.in_heredoc = 0;
	parse_envp(global);
	init_signals(global->heredoc_struct);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_global	global;

	if (argc != 1 || argv[1])
	{
		printf("This program does not accept arguments\n");
		exit(0);
	}
	global.envp = ft_arrdup(envp);
	find_pwd(&global);
	init_global_struct(&global);
	run_minishell(&global);
	return (0);
}
