/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:50:20 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/07/02 14:24:19 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_print_struct(t_list *pipex_list)
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
	t_list	*pipex_list;
	t_list	*tmp;
	t_files	*files;

	if (ac < 5)
		exit (write (2, "Arguments count error\n", 22));
	files = open_files(ac, av);
	pipex_list = pipex_parse(ac, av, envp, files);
	if (files->open == 1)
		execute_commands(&pipex_list, files, envp);
	free_pipex_struct(&pipex_list);
	close(files->infile);
	close(files->outfile);
	if (files->heredoc)
		unlink(".here_doc");
	free(files);
	return (0);
}
