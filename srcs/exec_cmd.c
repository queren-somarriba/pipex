/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:52:09 by qsomarri          #+#    #+#             */
/*   Updated: 2024/10/02 16:42:46 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**ft_parse_path(char **envp)
{
	char	*getpaths;
	char	**paths;
	size_t	i;

	getpaths = NULL;
	paths = NULL;
	i = 0;
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			getpaths = ft_substr(*envp, 5, ft_strlen(*envp) - 4);
			break ;
		}
		envp++;
	}
	if (!getpaths)
		return (perror("command path not found"), NULL);
	paths = ft_split(getpaths, ':');
	free(getpaths);
	if (!paths)
		return (NULL);
	return (paths);
}

static int	ft_xpath(char *argv_path, char **envp)
{
	char	*tmp;
	char	**cmd;
	size_t	len;

	len = ft_strlen(argv_path);
	while (argv_path[len] != '/')
		len--;
	len++;
	tmp = ft_substr(argv_path, len, ft_strlen(argv_path) - len + 1);
	if (!tmp)
		return (EXIT_FAILURE);
	cmd = ft_split(tmp, ' ');
	free(tmp);
	if (access(argv_path, X_OK) == 0)
	{
		if (execve(argv_path, cmd, envp) == -1)
			return (ft_free_tab(cmd), perror("execve"), EXIT_FAILURE);
	}
	return (ft_free_tab(cmd), EXIT_SUCCESS);
}

static int	ft_xcmd(char **paths, char **cmd, char **envp)
{
	size_t	i;
	char	*tmp;

	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = ft_strjoin(tmp, cmd[0]);
		free(tmp);
		if (access(paths[i], X_OK) == 0)
		{
			if (execve(paths[i], cmd, envp) == -1)
				return (ft_free_tab(paths), (ft_free_tab(cmd),
						perror("execve"), EXIT_FAILURE));
		}
	}
	if (!paths[i])
	{
		ft_free_tab(paths);
		ft_free_tab(cmd);
		return (perror("command not found"), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_xargv(char *argv, char **envp)
{
	char	**cmd;
	char	**paths;

	cmd = NULL;
	paths = NULL;
	if (access(argv, X_OK) == 0)
	{
		if (ft_xpath(argv, envp) == -1)
			return (EXIT_FAILURE);
	}
	else
	{
		cmd = ft_split(argv, ' ' );
		if (!cmd)
			return (EXIT_FAILURE);
		paths = ft_parse_path(envp);
		if (!paths)
			return (ft_free_tab(cmd), EXIT_FAILURE);
		if (ft_xcmd(paths, cmd, envp) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}
