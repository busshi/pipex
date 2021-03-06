/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 14:23:46 by aldubar           #+#    #+#             */
/*   Updated: 2021/06/29 17:22:34 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	redir(int i, t_data *data, int *pipefd)
{
	int		ret;

	ret = 0;
	if (i)
		dup2(pipefd[-2], STDIN_FILENO);
	else
		ret = choose_redir(data->av[1], IN);
	if (i)
		ret = choose_redir(data->av[4], OUT);
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
	childpid = fork();
	if (!childpid)
	{
		ret = redir(i, data, pipefd);
		if (ret)
			exit_pipex(i + 1, args, data, 2);
		close_pipe(pipefd - (i * 2), i + 1);
		if (!data->path)
		{
			paths = find_env_path(data->env);
			data->path = find_bin_path(args[0], paths);
			if (!data->path)
				exit_pipex(i + 1, args, data, 127);
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

static int	wait_signal(t_data *data, pid_t lastpid)
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
			close_pipe(data->pipefd, 2);
		if (pid == lastpid)
			ret = WEXITSTATUS(status);
		i++;
	}
	free(data->pipefd);
	free(data);
	close_fd();
	return (ret);
}

int	main(int ac, char **av, char **envp)
{
	t_data	*data;
	pid_t	pid;

	data = NULL;
	if (ac != 5)
		exit_error(ARGUMENTS_ERROR);
	else
	{
		data = init_data(av, envp);
		if (!data)
			return (1);
		pid = exec_cmd(data->pipefd, 0, data);
		pid = exec_cmd(data->pipefd + 2, 1, data);
		return (wait_signal(data, pid));
	}
	return (0);
}
