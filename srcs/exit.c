/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 01:37:04 by aldubar           #+#    #+#             */
/*   Updated: 2021/06/29 15:11:56 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	close_pipe(int *pipefd, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		close((pipefd + (i * 2))[0]);
		close((pipefd + (i * 2))[1]);
		i++;
	}
}

void	close_fd(void)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

void	exit_pipex(int i, char **args, t_data *data, int status)
{
	close_pipe(data->pipefd, i);
	ft_free_tab(args);
	free(data->pipefd);
	if (data->path)
	{
		free(data->path);
		data->path = NULL;
	}
	free(data);
	close_fd();
	exit(status);
}

void	exit_error(enum e_err error)
{
	if (error == ARGUMENTS_ERROR)
	{
		ft_putstr_fd("Wrong number of arguments!\n", 2);
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
	}
	else if (error == SPLIT_ERROR)
		ft_putstr_fd("ft_split error!\n", 2);
	close_fd();
	exit(1);
}
