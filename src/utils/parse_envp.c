/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddzuba <ddzuba@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:16:57 by hboichuk          #+#    #+#             */
/*   Updated: 2023/04/02 17:35:55 by ddzuba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_pwd(t_global *global)
{
	int	i;

	i = 0;
	while (global->envp[i])
	{
		if (!ft_strncmp(global->envp[i], "PWD=", 4))
			global->pwd = ft_substr(global->envp[i],
					4, ft_strlen(global->envp[i]) - 4);
		if (!ft_strncmp(global->envp[i], "OLDPWD=", 7))
			global->old_pwd = ft_substr(global->envp[i],
					7, ft_strlen(global->envp[i]) - 7);
		i++;
	}
	return (1);
}

char	*find_path(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5));
		i++;
	}
	return (ft_strdup("\0"));
}

int	parse_envp(t_global *global)
{
	char	*path_from_envp;
	int		i;
	char	*tmp;

	path_from_envp = find_path(global->envp);
	global->paths = ft_split(path_from_envp, ':');
	free(path_from_envp);
	i = 0;
	while (global->paths[i])
	{
		if (ft_strncmp(&global->paths[i][ft_strlen(global->paths[i]) - 1],
			"/", 1) != 0)
		{
			tmp = ft_strjoin(global->paths[i], "/");
			free(global->paths[i]);
			global->paths[i] = tmp;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
