/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler@student.42.fr <lsohler>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:55:33 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/05/12 11:42:01 by lsohler@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**pipex_path_array(char **envp)
{
	char **path_array;
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
	return (NULL);
}

px_list	*pipex_lstnew(int ac, char **av, int i, char **envp)
{
	px_list *list;

	list = malloc(sizeof (px_list));
	//printf("malloc test\n");
	if (!list )
		return (NULL);
	list->cmd = ft_split(av[i], ' ');
	list->path = pipex_path(list->cmd[0], envp);
	list->next = NULL;
	list->prev = NULL;
	return (list);
}

px_list	*pipex_parse(int ac, char **av, char **envp)
{
	px_list	*pipex_list;
	px_list	*top;
	int		i;

	i = 2;
	pipex_list = pipex_lstnew(ac, av, i, envp);
	top = pipex_list;
	while (++i < ac - 1)
	{
		pipex_list->next = pipex_lstnew(ac, av, i, envp);
		pipex_list->next->prev = pipex_list;
		pipex_list->child_n = i -2;
		pipex_list = pipex_list->next;
	}
	pipex_list->child_n = -1;
	return (top);
}

f_list	*open_files(int ac, char **av)
{
	f_list *files;

	files = malloc(sizeof (f_list));
	if (access(av[1], F_OK))
		exit (error_msg("Invalid infile\n"));
	files->infile = open(av[1], O_RDONLY);
	files->outfile = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0777);
	//printf("infile: %i\noutfile: %i\n", (*files)->infile, (*files)->outfile);
	if (files->infile < 0 || files->outfile < 0)
		exit (error_msg("Open error\n"));
	files->open = 1;
	return (files);
}