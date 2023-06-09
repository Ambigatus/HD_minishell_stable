/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddzuba <ddzuba@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 22:38:41 by ddzuba            #+#    #+#             */
/*   Updated: 2023/04/12 22:29:42 by ddzuba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	lexer(t_global *global)
{
	char	*tmp;

	tmp = ft_strtrim(global->args, " ");
	free(global->args);
	global->args = tmp;
	if (!global->args)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	if (global->args[0] == '\0')
		return (reset(global));
	add_history(global->args);
	if (!count_quotes(global->args))
		return (ft_error(2, global));
	if (!token_reader(global))
		return (ft_error(1, global));
	return (0);
}
