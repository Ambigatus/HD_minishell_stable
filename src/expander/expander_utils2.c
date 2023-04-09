/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddzuba <ddzuba@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:20:01 by fpolycar          #+#    #+#             */
/*   Updated: 2023/04/09 22:57:27 by ddzuba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	question_mark(char **tmp, t_heredoc heredoc_struct)
{
	free(*tmp);
	*tmp = ft_itoa(heredoc_struct.error_num);
	return (ft_strlen(*tmp) + 1);
}
