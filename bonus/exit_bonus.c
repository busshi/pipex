/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 01:37:04 by aldubar           #+#    #+#             */
/*   Updated: 2021/06/29 02:48:38 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	exit_error(enum e_err error)
{
	if (error == ARGUMENTS_ERROR)
	{
		ft_putstr_fd("Wrong number of arguments!\n", 2);
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 ... cmdn outfile\n", 2);
		exit (1);
	}
	else if (error == PATH_ERROR)
		ft_putstr_fd("PATH environment variable is missing!\n", 2);
	else if (error == SPLIT_ERROR)
		ft_putstr_fd("ft_split error!\n", 2);
	exit(1);
}

void	close_fd(int i, int len, int *fd)
{
	if (!i && fd[0] != -1)
	{
		if (close(fd[0]))
			ft_putstr_fd("fd close error!\n", 2);
	}
	if (i == len && fd[1] != -1)
	{
		if (close(fd[1]))
			ft_putstr_fd("fd close error!\n", 2);
	}
}
