/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 22:35:37 by aldubar           #+#    #+#             */
/*   Updated: 2021/06/29 02:51:02 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

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
