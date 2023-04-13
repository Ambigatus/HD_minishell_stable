/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddzuba <ddzuba@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:13:32 by hboichuk          #+#    #+#             */
/*   Updated: 2023/04/13 11:42:44 by ddzuba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	unset_error(t_simple_cmds *simple_cmd)
{
	int		i;

	i = 0;
	if (!simple_cmd->str[1])
	{
		ft_putendl_fd("minishell: unset: not enough arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	while (simple_cmd->str[1][i])
	{
		if (simple_cmd->str[1][i++] == '/')
		{
			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(simple_cmd->str[1], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
	}
	if (equal_sign(simple_cmd->str[1]) != 0)
	{
		ft_putendl_fd("minishell: unset: not a valid identifier",
			STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	delete_env_var(t_global *global, char *key)
{
    int i;
    int j;

    i = -1;
    while (global->envp[++i])
    {
        if (!ft_strncmp(global->envp[i], key, ft_strlen(key)))
        {
            free(global->envp[i]);
            j = i;
            while (global->envp[++j])
                global->envp[j - 1] = global->envp[j];
            global->envp[j - 1] = NULL;
            break ;
        }
    }
}

int	ft_unset(t_global *global, t_simple_cmds *simple_cmd)
{
    int 	i;
	char	**tmp;

	tmp = simple_cmd->str;
	if (unset_error(simple_cmd) == 1)
		return (EXIT_FAILURE);
    i = 1;
    while (tmp[i])
    {
        if (ft_strchr(tmp[i], '='))
            ft_dprintf(2, "unset: `%s': not a valid identifier\n", tmp[i]);
        else
            delete_env_var(global, tmp[i]);
        i++;
    }
    return (0);
}

