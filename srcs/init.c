/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 22:35:37 by aldubar           #+#    #+#             */
/*   Updated: 2021/06/28 17:45:40 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	open_fd(t_data *data)
{
	int		error;

	error = 0;
	data->fd[0] = open(data->av[1], O_RDONLY);
	if (data->fd[0] <= 0)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(data->av[1], STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		error++;
	}
	data->fd[1] = open(data->av[4], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (data->fd[1] <= 0)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(data->av[4], STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		error++;
	}
	return (error);
}

t_data	*init_data(char **av, char **envp)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->path = NULL;
	data->env = envp;
	data->av = av;
//	data->len = ac - 3;
	data->pipefd = (int *)malloc(sizeof(int) * 4);
	if (!data->pipefd)
	{
		free(data);
		return (NULL);
	}
	if (open_fd(data))
	{
		free(data->pipefd);
		free(data);
		return (NULL);
	}
	return (data);
}
