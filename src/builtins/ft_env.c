/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddzuba <ddzuba@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:09:05 by hboichuk	       #+#    #+#             */
/*   Updated: 2023/03/28 23:02:17 by ddzuba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_env(t_global *global, t_simple_cmds *simple_cmd)
{
	int		i;

	(void) simple_cmd;
	i = 0;
	while (global->envp[i])
	{
		ft_putendl_fd(global->envp[i], STDOUT_FILENO);
		i++;
	}
	return (EXIT_SUCCESS);
}
