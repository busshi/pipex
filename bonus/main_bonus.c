/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 14:23:46 by aldubar           #+#    #+#             */
/*   Updated: 2021/06/29 02:54:25 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static void	close_pipe(int *pipefd, int len)
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

static int	choose_redir(char *file, enum e_redir redir)
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

static int	redir(int i, t_data *data, int *pipefd)
{
	int		ret;

	ret = 0;
	if (i)
		dup2(pipefd[-2], STDIN_FILENO);
	else
		ret = choose_redir(data->av[1], IN);
	if (i == data->len - 1)
		ret = choose_redir(data->av[data->ac - 1], OUT);
	else
		dup2(pipefd[1], STDOUT_FILENO);
	return (ret);
}

static int	exec_dup(int *pipefd, int i, char **args, t_data *data)
{
	pid_t	childpid;
	char	*paths;
	int		ret;

	pipe(pipefd);
	ret = redir(i, data, pipefd);
	childpid = fork();
	if (!childpid)
	{
		close_pipe(pipefd - (i * 2), i + 1);
		if (ret)
			exit(2);
		if (!data->path)
		{
			paths = find_env_path(data->env);
			data->path = find_bin_path(args[0], paths);
			if (!data->path)
				exit(127);
		}
		return (execve(data->path, args, data->env));
	}
	else
		return (childpid);
}

static int	exec_cmd(int *pipefd, int i, t_data *data)
{
	char	**args;
	int		ret;

	args = ft_split(data->av[i + 2], ' ');
	if (!args)
	{
		free(data->pipefd);
		free(data);
		exit_error(SPLIT_ERROR);
	}
	if (!access(args[0], X_OK))
		data->path = ft_strdup(args[0]);
	ret = exec_dup(pipefd, i, args, data);
	if (data->path)
		free(data->path);
	data->path = NULL;
	ft_free_tab(args);
	return (ret);
}

static int	wait_signal(t_data *data, pid_t lastpid, int *pipefd)
{
	int		i;
	int		status;
	int		ret;
	pid_t	pid;

	i = 0;
	ret = 0;
	while (1)
	{
		pid = wait(&status);
		if (pid <= 0)
			break ;
		if (!i)
			close_pipe(pipefd, data->len);
		if (pid == lastpid)
			ret = WEXITSTATUS(status);
		i++;
	}
	free(data->pipefd);
	free(data);
	return (ret);
}

static int	pipex(t_data *data)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < data->len)
	{
		pid = exec_cmd(data->pipefd + (i * 2), i, data);
		i++;
	}
	return (wait_signal(data, pid, data->pipefd));
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	data = NULL;
	if (ac < 4)
		exit_error(ARGUMENTS_ERROR);
	else
	{
		data = init_data(ac, av, env);
		if (!data)
			return (1);
		return (pipex(data));
	}
	return (0);
}
