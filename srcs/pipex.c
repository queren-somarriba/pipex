/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:27:13 by qsomarri          #+#    #+#             */
/*   Updated: 2024/10/02 16:47:00 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_init_fd_in(t_pipex *data)
{
	int	fd_in;
	int	pipefd[2];

	fd_in = ft_open(data->av[1], O_RDONLY, 1);
	if (fd_in == -1)
	{
		ft_pipe(data, pipefd);
		ft_close(data, pipefd[1]);
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			return (perror("dup2"), ft_close(data, pipefd[0]), EXIT_FAILURE);
		ft_close(data, pipefd[0]);
		return (-1);
	}
	if (fd_in != -1)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			return (perror("dup2"), ft_close(data, fd_in), EXIT_FAILURE);
		ft_close(data, fd_in);
	}
	return (EXIT_SUCCESS);
}

static int	pipex_bonus(t_pipex *data)
{
	int		i;

	i = 1;
	if (ft_init_fd_in(data) == -1)
		i++;
	while (++i < data->ac - 2)
	{
		if (run_cmds(data, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if (run_cmds(data, i) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	int		res;
	t_pipex	*data;

	data = NULL;
	if (argc == 5)
	{
		data = malloc(sizeof(t_pipex));
		if (!data)
			return (1);
		data->ac = argc;
		data->av = argv;
		data->env = envp;
		data->exit_status = 0;
		if (pipex_bonus(data))
		{
			if (data->exit_status == 0)
				data->exit_status = 1;
		}
		res = data->exit_status;
		return (free(data), res);
	}
	else
		ft_putstr_fd("Please try format : infile cmd1 cmd2 outfile\n", 2);
	return (127);
}
