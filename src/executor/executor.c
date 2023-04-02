/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddzuba <ddzuba@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:09:50 by hboichuk          #+#    #+#             */
/*   Updated: 2023/04/02 21:30:08 by ddzuba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_simple_cmds	*call_expander(t_global *global, t_simple_cmds *cmd)
{
	t_token	*start;

	cmd->str = expander(global, cmd->str);
	start = cmd->redirections;
	while (cmd->redirections)
	{
		if (cmd->redirections->token != LESS_LESS)
			cmd->redirections->str
				= expander_str(global, cmd->redirections->str);
		cmd->redirections = cmd->redirections->next;
	}
	cmd->redirections = start;
	return (cmd);
}

int	pipe_wait(t_global *global)
{
	int	i;
	int	status;

	i = 0;
	while (i < global->pipes)
	{
		waitpid(global->pid[i], &status, 0);
		i++;
	}
	waitpid(global->pid[i], &status, 0);
	if (WIFEXITED(status))
		global->heredoc_struct.error_num = WEXITSTATUS(status);
	return (EXIT_SUCCESS);
}

int	ft_fork(t_global *global, int end[2], int fd_in, t_simple_cmds *cmd)
{
	static int	i = 0;

	if (global->reset == true)
	{
		i = 0;
		global->reset = false;
	}
	global->pid[i] = fork();
	if (global->pid[i] < 0)
		ft_error(5, global);
	if (global->pid[i] == 0)
		dup_cmd(cmd, global, end, fd_in);
	i++;
	return (EXIT_SUCCESS);
}

int	check_fd_heredoc(t_global *global, int end[2], t_simple_cmds *cmd)
{
	int	fd_in;

	if (global->heredoc)
	{
		close(end[0]);
		fd_in = open(cmd->hd_file_name, O_RDONLY);
	}
	else
		fd_in = end[0];
	return (fd_in);
}

int	executor(t_global *global)
{
	int		end[2];
	int		fd_in;

	fd_in = STDIN_FILENO;
	while (global->simple_cmds)
	{
		global->simple_cmds = call_expander(global, global->simple_cmds);
		if (global->simple_cmds->next)
			pipe(end);
		send_heredoc(global, global->simple_cmds);
		ft_fork(global, end, fd_in, global->simple_cmds);
		close(end[1]);
		if (global->simple_cmds->prev)
			close(fd_in);
		fd_in = check_fd_heredoc(global, end, global->simple_cmds);
		if (global->simple_cmds->next)
			global->simple_cmds = global->simple_cmds->next;
		else
			break ;
	}
	pipe_wait(global);
	global->simple_cmds = ft_simple_cmdsfirst(global->simple_cmds);
	return (0);
}
