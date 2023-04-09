/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddzuba <ddzuba@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 11:52:02 by hboichuk          #+#    #+#             */
/*   Updated: 2023/04/09 22:57:53 by ddzuba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_parser_cmd	init_parser_tools(t_token *lexer_list, t_global *global)
{
	t_parser_cmd	parser_tools;

	parser_tools.lexer_list = lexer_list;
	parser_tools.redirections = NULL;
	parser_tools.num_redirections = 0;
	parser_tools.tools = global;
	return (parser_tools);
}

void	count_pipes(t_token *lexer_list, t_global *global)
{
	t_token	*tmp;

	tmp = lexer_list;
	global->pipes = 0;
	while (tmp)
	{
		if (tmp->token == PIPE)
			global->pipes++;
		tmp = tmp->next;
	}
}

int	count_args(t_token *lexer_list)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = lexer_list;
	while (tmp && tmp->token != PIPE)
	{
		if (tmp->i >= 0)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

t_token	*find_next_cmd(t_token *lexer_lst)
{
	while (lexer_lst && lexer_lst->token != PIPE)
		lexer_lst = lexer_lst->next;
	return (lexer_lst);
}
