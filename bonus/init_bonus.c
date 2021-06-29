/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 22:35:37 by aldubar           #+#    #+#             */
/*   Updated: 2021/06/29 12:15:02 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	choose_redir(char *file, enum e_redir redir)
{
	int		fd;

	if (redir == IN)
		fd = open(file, O_RDONLY);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		return (1);
	}
	if (redir == IN)
		dup2(fd, STDIN_FILENO);
	else if (redir == OUT)
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

t_data	*init_data(int ac, char **av, char **env)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->path = NULL;
	data->env = env;
	data->av = av;
	data->ac = ac;
	data->len = ac - 3;
	data->pipefd = (int *)malloc(sizeof(int) * (2 * data->len));
	if (!data->pipefd)
	{
		free(data);
		return (NULL);
	}
	return (data);
}
