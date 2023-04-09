/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddzuba <ddzuba@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:24:04 by hboichuk          #+#    #+#             */
/*   Updated: 2023/04/09 22:57:14 by ddzuba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*join_split_str(char **split_str, char *new_str);
char	**resplit_str(char **double_arr);

int	find_cmd(t_simple_cmds *cmd, t_global *global)
{
	int		i;
	char	*mycmd;

	i = 0;
	cmd->str = resplit_str(cmd->str);
	if (!access(cmd->str[0], F_OK))
		execve(cmd->str[0], cmd->str, global->envp);
	while (global->paths[i])
	{
		mycmd = ft_strjoin(global->paths[i], cmd->str[0]);
		if (!access(mycmd, F_OK))
			execve(mycmd, cmd->str, global->envp);
		free(mycmd);
		i++;
	}
	return (cmd_not_found(cmd->str[0]));
}

void	handle_cmd(t_simple_cmds *cmd, t_global *global)
{
	int	exit_code;

	exit_code = 0;
	if (cmd->redirections)
		if (check_redirections(cmd))
			exit(1);
	if (cmd->builtin != NULL)
	{
		exit_code = cmd->builtin(global, cmd);
		exit(exit_code);
	}
	else if (cmd->str[0][0] != '\0')
		exit_code = find_cmd(cmd, global);
	exit(exit_code);
}

void	dup_cmd(t_simple_cmds *cmd, t_global *global, int end[2], int fd_in)
{
	if (cmd->prev && dup2(fd_in, STDIN_FILENO) < 0)
		ft_error(4, global);
	close(end[0]);
	if (cmd->next && dup2(end[1], STDOUT_FILENO) < 0)
		ft_error(4, global);
	close(end[1]);
	if (cmd->prev)
		close(fd_in);
	handle_cmd(cmd, global);
}

void	single_cmd(t_simple_cmds *cmd, t_global *global)
{
	int	pid;
	int	status;

	global->simple_cmds = call_expander(global, global->simple_cmds);
	if (cmd->builtin == ft_cd || cmd->builtin == ft_exit
		|| cmd->builtin == ft_export || cmd->builtin == ft_unset)
	{
		global->heredoc_struct.error_num = cmd->builtin(global, cmd);
		return ;
	}
	send_heredoc(global, cmd);
	pid = fork();
	if (pid < 0)
		ft_error(5, global);
	if (pid == 0)
		handle_cmd(cmd, global);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		global->heredoc_struct.error_num = WEXITSTATUS(status);
}
