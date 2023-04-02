/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddzuba <ddzuba@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:13:08 by hboichuk          #+#    #+#             */
/*   Updated: 2023/04/02 19:29:33 by ddzuba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pwd(t_global *global, t_simple_cmds *simple_cmd)
{
	(void) simple_cmd;
	ft_putendl_fd(global->pwd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
