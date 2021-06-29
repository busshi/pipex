/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 14:24:28 by aldubar           #+#    #+#             */
/*   Updated: 2021/06/28 18:00:13 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/errno.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum e_err
{
	ARGUMENTS_ERROR,
	FD_OPEN_ERROR,
	PATH_ERROR,
	SPLIT_ERROR,
}		t_err;
/*
typedef struct s_data
{
	int		fd[2];
	int		*pipefd;
	char	**env;
	char	**av;
	char	*path;
//	int		len;
}		t_data;*/

//t_data	*init_data(char **av, char **env);
void	run_cmd(char **av, char **env, int *fd);
char	*find_env_path(char **env);
char	*find_bin_path(char *cmd, char *path);
void	close_fd(int i, int *fd);
int		error_msg(enum e_err error, char *s);
int		exit_error(enum e_err error);
size_t	ft_strlen(const char *s);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_free_tab(char **tab);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
