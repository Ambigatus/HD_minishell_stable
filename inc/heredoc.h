/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddzuba <ddzuba@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:56:00 by ddzuba            #+#    #+#             */
/*   Updated: 2023/04/02 21:12:32 by ddzuba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef 	HEREDOC_H
# define HEREDOC_H

#include "minishell.h"

/*		HEREDOC STRUCT		*/
typedef struct s_heredoc
{
	int	error_num;
	int	stop_heredoc;
	int	in_cmd;
	int	in_heredoc;
}	t_heredoc;

// t_heredoc	heredoc_struct;


#endif