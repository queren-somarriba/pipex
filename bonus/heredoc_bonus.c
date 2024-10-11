/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:20:55 by qsomarri          #+#    #+#             */
/*   Updated: 2024/10/02 12:07:09 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	ft_make_heredoc(t_pipex *data, int *pipefd, char *limiter)
{
	char	*line;

	ft_putstr_fd("here_doc> ", STDIN_FILENO);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (!ft_strncmp(line, limiter, ft_strlen(limiter))
			&& ft_strlen(line) - 1 == ft_strlen(limiter))
		{
			free(line);
			ft_close(data, *pipefd);
			free(data);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(line, *pipefd);
		free(line);
		ft_putstr_fd("here_doc> ", STDIN_FILENO);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	ft_close(data, *pipefd);
	free(data);
	exit(EXIT_FAILURE);
}

int	ft_get_heredoc(t_pipex *data, char *limiter)
{
	pid_t	pid;
	int		pipefd[2];

	ft_pipe(data, pipefd);
	pid = ft_fork(data);
	if (pid == 0)
	{
		ft_close(data, pipefd[0]);
		if (ft_make_heredoc(data, &pipefd[1], limiter) == EXIT_FAILURE)
			return (ft_close(data, pipefd[1]), EXIT_FAILURE);
		ft_close(data, pipefd[1]);
	}
	else if (pid > 0)
	{
		waitpid(pid, NULL, 0);
		ft_close(data, pipefd[1]);
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			return (perror("dup2"), ft_close(data, pipefd[0]), EXIT_FAILURE);
		ft_close(data, pipefd[0]);
	}
	return (EXIT_SUCCESS);
}
