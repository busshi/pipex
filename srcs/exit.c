/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 01:37:04 by aldubar           #+#    #+#             */
/*   Updated: 2021/06/29 12:34:40 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	exit_error(enum e_err error)
{
	if (error == ARGUMENTS_ERROR)
	{
		ft_putstr_fd("Wrong number of arguments!\n", 2);
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
		exit (1);
	}
	else if (error == PATH_ERROR)
		ft_putstr_fd("PATH environment variable is missing!\n", 2);
	else if (error == SPLIT_ERROR)
		ft_putstr_fd("ft_split error!\n", 2);
	exit(1);
}

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
