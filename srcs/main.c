/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 14:23:46 by aldubar           #+#    #+#             */
/*   Updated: 2021/06/28 22:04:25 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	exec_dup(int *pipefd, int i, char **args, char **envp, char *bin_path, int *fd)
//static int	exec_dup(int *pipefd, int i, char **args, t_data *data)
{
	pid_t	childpid;
	char	*paths;

	pipe(pipefd);
	childpid = fork();
	if (!childpid)
	{
//		if (!data->path)
		if (!bin_path)
		{
			paths = find_env_path(envp);
		//	paths = find_env_path(data->env);
			bin_path = find_bin_path(args[0], paths);
			//data->path = find_bin_path(args[0], paths);
			//if (!data->path)
			if (!bin_path)
				exit(127);
		}
		if (!i)
//			dup2(data->fd[0], STDIN_FILENO);
			dup2(fd[0], STDIN_FILENO);
		else
			dup2(pipefd[-2], STDIN_FILENO);
		if (i)
			dup2(fd[1], STDOUT_FILENO);
			//dup2(data->fd[1], STDOUT_FILENO);
		else
			dup2(pipefd[1], STDOUT_FILENO);
	//	return (execve(data->path, args, data->env));
		return (execve(bin_path, args, envp));
	}
	else
		return (childpid);

}

static int	exec_cmd(int *pipefd, int i, char **av, char **envp, int *fd)
//static int	exec_cmd(int *pipefd, int i, t_data *data)
{
	char	**args;
	int		ret;
	char	*bin_path;

	args = ft_split(av[i + 2], ' ');
//	args = ft_split(data->av[i + 2], ' ');
	if (!args)
	{
//		free(data->pipefd);
//		free(data);
		free(pipefd);
		exit_error(SPLIT_ERROR);
	}
	bin_path = NULL;
	if (!access(args[0], X_OK))
		bin_path = ft_strdup(args[0]);
//		data->path = ft_strdup(args[0]);
//	ret = exec_dup(pipefd, i, args, data);
	ret = exec_dup(pipefd, i, args, envp, bin_path, fd);
	if (bin_path)
		free(bin_path);
	bin_path = NULL;
//	if (data->path)
//		free(data->path);
//	data->path = NULL;
	ft_free_tab(args);
	return (ret);
}

static int	wait_pid(pid_t lastpid, int *pipefd)
//static int	wait_pid(pid_t pid, t_data *data)
{
	pid_t	pid;
	int		ret;
	int		status;
	int		i;

	ret = 0;
	i = 0;
	while (1)
	{
		pid = wait(&status);
		if (pid <= 0)
			break ;
		if (!i)
		{
			close(pipefd[0]);
			close(pipefd[1]);
			close(pipefd[2]);
			close(pipefd[3]);
		}
		if (pid == lastpid)
			ret = WEXITSTATUS(status);
		i++;
	}
	free(pipefd);
//	free(data->pipefd);
//	free(data);
	return (ret);
}

static int	pipex(char **av, char **envp, int *pipefd)
//static int	pipex(t_data *data)
{
	int		i;
	int		*current_pipefd;
	pid_t		pid;
	int		fd[2];

	fd[0] = open(av[1], O_RDONLY);
	if (fd[0] <= 0)
		return (error_msg(FD_OPEN_ERROR, av[1]));
	fd[1] = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd[1] <= 0)
		return (error_msg(FD_OPEN_ERROR, av[4]));
	i = 0;
	while (i < 2)
	{
		//current_pipefd = data->pipefd + (i * 2);
		current_pipefd = pipefd + (i * 2);
		pipe(current_pipefd);
		pid = exec_cmd(pipefd + (i * 2), i, av, envp, fd);
		//pid = exec_cmd(data->pipefd + (i * 2), i, data);
		if (i && current_pipefd[-2] != -1)
		{
			close(current_pipefd[-2]);
			current_pipefd[-2] = -1;
		}
		close(current_pipefd[1]);
		current_pipefd[1] = -1;
		//close_fd(i, data->fd);
		close_fd(i, fd);
		i++;
	}
	return (wait_pid(pid, pipefd));
	//return (wait_pid(pid, data));
}

int	main(int ac, char **av, char **envp)
{
//	t_data	*data;
	int		*pipefd;

//	data = NULL;
	if (ac != 5)
		return (exit_error(ARGUMENTS_ERROR));
	else
	{
//		data = init_data(av, envp);
//		if (!data)
//			return (1);
//		return (pipex(data));
		pipefd = (int *)malloc(sizeof(int) * 4);
		if (!pipefd)
			return (1);
		return (pipex(av, envp, pipefd));
	}
	return (0);
}
