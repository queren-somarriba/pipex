/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:40:42 by qsomarri          #+#    #+#             */
/*   Updated: 2024/10/03 14:59:03 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/includes/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_pipex
{
	int		ac;
	int		exit_status;
	char	**av;
	char	**env;
}		t_pipex;

/*EXEC_CMD*/
int	ft_xargv(char *argv, char **envp);

/*PIPEX_UTILS*/
int	ft_fork(t_pipex *data);

int	ft_pipe(t_pipex *data, int *pipedes);

int	ft_close(t_pipex *data, int fd);

int	ft_open(const char *file, int oflag, int mode);

/*PROCESS*/
int	run_cmds(t_pipex *data, int index);

#endif