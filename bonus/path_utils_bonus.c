/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 01:36:07 by aldubar           #+#    #+#             */
/*   Updated: 2021/06/27 00:51:51 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char	*find_env_path(char **env)
{
	int		i;
	char	*path;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp("PATH=", env[i], 5))
		{
			path = ft_strdup(env[i] + 5);
			return (path);
		}
		i++;
	}
	return (NULL);
}

static char	**split_env_path(char *cmd, char *path)
{
	char	**paths;
	char	*tmp;
	int		i;

	paths = ft_split(path, ':');
	if (!paths)
	{
		free(path);
		return (NULL);
	}
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = ft_strjoin(tmp, cmd);
		free(tmp);
		i++;
	}
	free(path);
	return (paths);
}

char	*find_bin_path(char *cmd, char *path)
{
	char	**paths;
	char	*bin_path;
	int		i;

	paths = split_env_path(cmd, path);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		if (!access(paths[i], X_OK))
		{
			bin_path = ft_strdup(paths[i]);
			ft_free_tab(paths);
			return (bin_path);
		}
		i++;
	}
	ft_free_tab(paths);
	ft_putstr_fd("pipex: command not found: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (NULL);
}
