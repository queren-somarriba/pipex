/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:34:58 by qsomarri          #+#    #+#             */
/*   Updated: 2024/10/04 16:59:57 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_fork(t_pipex *data)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		free(data);
		exit(EXIT_FAILURE);
	}
	return (pid);
}

int	ft_pipe(t_pipex *data, int *pipedes)
{
	if (pipe(pipedes) == -1)
	{
		perror("pipe");
		free(data);
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_close(t_pipex *data, int fd)
{
	int	res;

	res = close(fd);
	if (res == -1)
	{
		perror("close");
		free(data);
		exit(EXIT_FAILURE);
	}
	return (res);
}

int	ft_open(const char *file, int oflag, int mode)
{
	int	res;

	if (mode == 1)
		res = open(file, oflag);
	if (mode == 2)
		res = open(file, oflag, 0644);
	if (res == -1)
		perror("open");
	return (res);
}
