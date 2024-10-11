/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:18:12 by qsomarri          #+#    #+#             */
/*   Updated: 2024/10/04 17:04:30 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	last_child(t_pipex *data)
{
	int	fd_out;

	if (data->ac >= 6 && !ft_strncmp(data->av[1], "here_doc", 8)
		&& ft_strlen(data->av[1]) == 8)
		fd_out = ft_open(data->av[data->ac - 1],
				O_CREAT | O_RDWR | O_APPEND, 2);
	else
		fd_out = ft_open(data->av[data->ac - 1], O_CREAT | O_RDWR | O_TRUNC, 2);
	if (fd_out == -1)
		return (EXIT_FAILURE);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		return (ft_close(data, fd_out), perror("dup2"), EXIT_FAILURE);
	ft_close(data, fd_out);
	return (EXIT_SUCCESS);
}

static int	child_process(t_pipex *data, int *pipefd, int index)
{
	ft_close(data, pipefd[0]);
	if (index == data->ac - 2)
	{
		if (last_child(data))
			return (ft_close(data, pipefd[1]), EXIT_FAILURE);
	}
	else
	{
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			return (perror("dup2"), ft_close(data, pipefd[1]), EXIT_FAILURE);
	}
	ft_close(data, pipefd[1]);
	if (ft_xargv(data->av[index], data->env) == EXIT_FAILURE)
	{
		free(data);
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	parent_process(t_pipex *data, pid_t pid, int *pipefd, int index)
{
	pid_t	endpid;
	int		status;

	ft_close(data, pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO == -1))
		return (ft_close(data, pipefd[0]), perror ("dup2"), EXIT_FAILURE);
	ft_close(data, pipefd[0]);
	if (index == data->ac - 2)
	{
		while (1)
		{
			endpid = waitpid(-1, &status, 0);
			if (endpid == pid)
				if (WIFEXITED(status))
					data->exit_status = WEXITSTATUS(status);
			if (endpid == -1)
				break ;
		}
	}
	return (EXIT_SUCCESS);
}

int	run_cmds(t_pipex *data, int index)
{
	pid_t	pid;
	int		pipefd[2];

	ft_pipe(data, pipefd);
	pid = ft_fork(data);
	if (!pid)
	{
		if (child_process(data, pipefd, index))
			return (EXIT_FAILURE);
	}
	if (pid)
		return (parent_process(data, pid, pipefd, index));
	return (EXIT_SUCCESS);
}
