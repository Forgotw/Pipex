/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:50:20 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/05/19 15:07:08 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void pipex_print_struct (px_list *pipex_list)
{
	size_t	i;

	i = 0;
	while (pipex_list != NULL)
	{
		printf("path: %s\ncmd:\n", pipex_list->path);
		while (pipex_list->cmd[i] != NULL)
		{
			printf("%s\n", pipex_list->cmd[i]);
			i++;
		}
		pipex_list = pipex_list->next;
		i = 0;
	}
}

int	main(int ac, char **av, char **envp)
{
	px_list	*pipex_list;
	px_list	*tmp;
	f_list	*files;
	
	/*if (ac < 5)
		exiterror("Arguments count error\n");*/
	files = open_files(ac, av);
	pipex_list = pipex_parse(ac, av, envp, files);
	if (files->open == 1)
		execute_commands(&pipex_list, files, envp);
	free_pipex_struct(&pipex_list);
	close(files->infile);
	close(files->outfile);
	free(files);
	return (0);
}