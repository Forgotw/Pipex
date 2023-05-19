/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:55:33 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/05/19 17:05:15 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**pipex_path_array(char **envp)
{
	char	**path_array;
	size_t	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp((envp[i]), "PATH=", 5) == 0)
		{
			path_array = ft_split(envp[i], ':');
			return (path_array);
		}
		i++;
	}
	return (NULL);
}

char	*pipex_path(char *cmd, char **envp)
{
	char	**path_array;
	char	*path;
	char	*tmp;
	size_t	i;

	path_array = pipex_path_array(envp);
	if (path_array[0] == NULL)
		return (NULL);
	i = 0;
	while (path_array[i] != NULL)
	{
		tmp = ft_strjoin(path_array[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, F_OK) == 0)
		{
			free_split(path_array);
			return (path);
		}
		free(path);
		i++;
	}
	free_split(path_array);
	return (cmd);
}

px_list	*pipex_lstnew(int ac, char **av, int i, char **envp)
{
	px_list	*list;

	list = malloc(sizeof (px_list));
	if (!list)
		return (NULL);
	list->cmd = ft_split(av[i], ' ');
	list->path = pipex_path(list->cmd[0], envp);
	if (!list->path)
	{
		write(2, "Command not found\n", 19);
		exit(EXIT_FAILURE);
	}
	list->next = NULL;
	list->prev = NULL;
	return (list);
}

px_list	*pipex_parse(int ac, char **av, char **envp, f_list *files)
{
	px_list	*pipex_list;
	px_list	*top;
	int		i;

	i = 2;
	if (files->heredoc == 1)
		i = 3;
	pipex_list = pipex_lstnew(ac, av, i, envp);
	top = pipex_list;
	while (++i < ac - 1)
	{
		pipex_list->next = pipex_lstnew(ac, av, i, envp);
		pipex_list->next->prev = pipex_list;
		pipex_list = pipex_list->next;
	}
	return (top);
}

f_list	*open_files(int ac, char **av)
{
	f_list	*files;
	char	*limiter;

	files = malloc(sizeof (f_list));
	here_doc_checker(av, files);
	if (files->heredoc == 0)
		files->infile = open(av[1], O_RDONLY);
	if (files->heredoc == 1)
	{
		limiter = ft_strjoin(av[2], "\n");
		here_doc_open(&files, limiter);
		free(limiter);
	}
	else
	{
		if (access(av[1], F_OK))
			perror_and_exit("Infile");
		files->outfile = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0777);
	}
	if (files->infile < 0 || files->outfile < 0)
		perror_and_exit("Open");
	files->open = 1;
	return (files);
}
