/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddzuba <ddzuba@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:42:39 by hboichuk          #+#    #+#             */
/*   Updated: 2023/04/02 20:45:51 by ddzuba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_heredoc(t_token *lst, bool quotes,
	t_global *global, char *file_name)
{
	int		fd;
	char	*line;

	fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	line = readline("Heredoc...");
	while (line && ft_strncmp(lst->str, line, ft_strlen(lst->str))
		&& !heredoc_struct.stop_heredoc)
	{
		if (quotes == false)
			line = expander_str(global, line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("Heredoc...");
	}
	free(line);
	if (heredoc_struct.stop_heredoc || !line)
		return (EXIT_FAILURE);
	close(fd);
	return (EXIT_SUCCESS);
}

int	ft_heredoc(t_global *tools, t_token *lst, char *file_name)
{
	bool	quotes;
	int		sl;

	sl = EXIT_SUCCESS;
	if ((lst->str[0] == '\"'
			&& lst->str[ft_strlen(lst->str) - 1] == '\"')
		|| (lst->str[0] == '\''
			&& lst->str[ft_strlen(lst->str) - 1] == '\''))
		quotes = true;
	else
		quotes = false;
	delete_quotes(lst->str, '\"');
	delete_quotes(lst->str, '\'');
	heredoc_struct.stop_heredoc = 0;
	heredoc_struct.in_heredoc = 1;
	sl = create_heredoc(lst, quotes, tools, file_name);
	heredoc_struct.in_heredoc = 0;
	tools->heredoc = true;
	return (sl);
}

char	*generate_heredoc_filename(void)
{
	static int	i = 0;
	char		*num;
	char		*file_name;

	num = ft_itoa(i++);
	file_name = ft_strjoin("build/.tmp_heredoc_file_", num);
	free(num);
	return (file_name);
}

int	send_heredoc(t_global *global, t_simple_cmds *cmd)
{
	t_token	*start;
	int		sl;

	start = cmd->redirections;
	sl = EXIT_SUCCESS;
	while (cmd->redirections)
	{	
		if (cmd->redirections->token == LESS_LESS)
		{
			if (cmd->hd_file_name)
				free(cmd->hd_file_name);
			cmd->hd_file_name = generate_heredoc_filename();
			sl = ft_heredoc(global, cmd->redirections, cmd->hd_file_name);
			if (sl)
			{
				heredoc_struct.error_num = 1;
				return (reset(global));
			}
		}
		cmd->redirections = cmd->redirections->next;
	}
	cmd->redirections = start;
	return (EXIT_SUCCESS);
}
