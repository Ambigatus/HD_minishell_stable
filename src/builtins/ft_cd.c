/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddzuba <ddzuba@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:17:04 by hboichuk          #+#    #+#             */
/*   Updated: 2023/04/07 21:12:04 by ddzuba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*find_path_ret(char *str, t_global *global)
{
	int	i;

	i = 0;
	while (global->envp[i])
	{
		if (!ft_strncmp(global->envp[i], str, ft_strlen(str)))
			return (ft_substr(global->envp[i], ft_strlen(str),
					ft_strlen(global->envp[i]) - ft_strlen(str)));
		i++;
	}
	return (NULL);
}

int	specific_path(t_global *global, char *str)
{
	char	*tmp;
	int		ret;

	tmp = find_path_ret(str, global);
	if (!tmp)
		return (0);
	ret = chdir(tmp);
	free(tmp);
	if (ret != 0)
	{
		str = ft_substr(str, 0, ft_strlen(str) - 1);
		ft_putstr_fd(str, STDERR_FILENO);
		free(str);
		ft_putendl_fd(" not set", STDERR_FILENO);
	}
	return (ret);
}

void	add_path_to_env(t_global *global)
{
	int		i;
	char	*tmp;

	i = 0;
	while (global->envp[i])
	{
		if (!ft_strncmp(global->envp[i], "PWD=", 4))
		{
			tmp = ft_strjoin("PWD=", global->pwd);
			free(global->envp[i]);
			global->envp[i] = tmp;
		}
		else if (!ft_strncmp(global->envp[i], "OLDPWD=", 7) && global->old_pwd)
		{
			tmp = ft_strjoin("OLDPWD=", global->old_pwd);
			free(global->envp[i]);
			global->envp[i] = tmp;
		}
		i++;
	}
}

int	ft_cd(t_global *global, t_simple_cmds *simple_cmd)
{
	int		ret;

	if (!simple_cmd->str[1])
		ret = specific_path(global, "HOME=");
	else if (ft_strncmp(simple_cmd->str[1], "-", 1) == 0)
		ret = specific_path(global, "OLDPWD=");
	else
	{
		ret = chdir(simple_cmd->str[1]);
		if (ret != 0)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(simple_cmd->str[1], STDERR_FILENO);
			perror(" ");
		}
	}
	if (ret != 0)
		return (EXIT_FAILURE);
	// change_path(global);
	add_path_to_env(global);
	return (EXIT_SUCCESS);
}
