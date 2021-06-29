/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 14:24:28 by aldubar           #+#    #+#             */
/*   Updated: 2021/06/29 12:57:22 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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
	PATH_ERROR,
	SPLIT_ERROR
}		t_err;

typedef enum e_redir
{
	IN,
	OUT
}		t_redir;

typedef struct s_data
{
	int		*pipefd;
	char	**env;
	char	**av;
	char	*path;
	int		ac;
	int		len;
}		t_data;

t_data	*init_data(int ac, char **av, char **env);
void	run_cmd(char **av, char **env, int *fd);
char	*find_env_path(char **env);
char	*find_bin_path(char *cmd, char *path);
int		choose_redir(char *file, enum e_redir redir);
void	close_pipe(int *pipefd, int len);
void	exit_pipex(int i, char **args, t_data *data, int status);
void	exit_error(enum e_err error);
size_t	ft_strlen(const char *s);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_free_tab(char **tab);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
