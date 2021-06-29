/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 01:37:04 by aldubar           #+#    #+#             */
/*   Updated: 2021/06/28 18:00:29 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	exit_error(enum e_err error)
{
	if (error == ARGUMENTS_ERROR)
	{
		ft_putstr_fd("Wrong number of arguments!\n", 2);
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 ... cmdn outfile\n", 2);
	}
	else if (error == PATH_ERROR)
		ft_putstr_fd("PATH environment variable is missing!\n", 2);
	else if (error == SPLIT_ERROR)
		ft_putstr_fd("ft_split error!\n", 2);
	return (1);
}

void	close_fd(int i, int *fd)
{
	if (!i && fd[0] != -1)
	{
		if (close(fd[0]))
			ft_putstr_fd("fd close error!\n", 2);
	}
	if (i && fd[1] != -1)
	{
		if (close(fd[1]))
			ft_putstr_fd("fd close error!\n", 2);
	}
}

int	error_msg(enum e_err error, char *s)
{
	if (error == FD_OPEN_ERROR)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(s, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	return (1);
}
