/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddzuba <ddzuba@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:28:22 by hboichuk          #+#    #+#             */
/*   Updated: 2023/04/11 11:40:04 by ddzuba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_parser(t_simple_cmds simple_cmds);

t_simple_cmds	*initialize_cmd(t_parser_cmd *parser_tools)
{
	char	**str;
	int		i;
	int		arg_size;
	t_token	*tmp;

	i = 0;
	rm_redirections(parser_tools);
	arg_size = count_args(parser_tools->lexer_list);
	str = ft_calloc(arg_size + 1, sizeof(char *));
	if (!str)
		parser_error(1, parser_tools->tools, parser_tools->lexer_list);
	tmp = parser_tools->lexer_list;
	while (arg_size > 0)
	{
		if (tmp->str)
		{
			str[i++] = ft_strdup(tmp->str);
			ft_lexerdelone(&parser_tools->lexer_list, tmp->i);
			tmp = parser_tools->lexer_list;
		}
		arg_size--;
	}
	return (ft_simple_cmdsnew(str,
			parser_tools->num_redirections, parser_tools->redirections));
}

int	handle_pipe_errors(t_global *global, t_symbol token)
{
	if (token == PIPE)
	{
		parser_double_token_error(global, global->lexer_list,
			global->lexer_list->token);
		return (EXIT_FAILURE);
	}
	if (!global->lexer_list)
	{
		parser_error(0, global, global->lexer_list);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	parser(t_global *global)
{
	t_simple_cmds	*node;
	t_parser_cmd	cmd;

	global->simple_cmds = NULL;
	count_pipes(global->lexer_list, global);
	while (global->lexer_list)
	{
		if (global->lexer_list->token == SEMICOLON \
			&& peek_token(global->lexer_list) == PIPE)
		{
			parser_double_token_error(global, global->lexer_list, PIPE);
			return (EXIT_FAILURE);
		}
		if (global->lexer_list->token == PIPE)
		{
			// if (handle_pipe_errors(global, global->lexer_list->token))
			// 	return (EXIT_FAILURE);
			global->lexer_list = global->lexer_list->next;
			continue ;
		}
		cmd = init_parser_tools(global->lexer_list, global);
		node = initialize_cmd(&cmd);
		if (!node)
			parser_error(0, global, cmd.lexer_list);
		if (!global->simple_cmds)
			global->simple_cmds = node;
		else
			ft_simple_cmdsadd_back(&global->simple_cmds, node);
		global->lexer_list = cmd.lexer_list;
	}
	return (EXIT_SUCCESS);
}
