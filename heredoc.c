/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:46:01 by lsohler           #+#    #+#             */
/*   Updated: 2023/07/02 14:15:48 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc_checker(char **av, t_files *files)
{
	if (!ft_strncmp("here_doc", av[1], ft_strlen("here_doc") + 1))
		files->heredoc = 1;
	else
		files->heredoc = 0;
}

void	here_doc_write(t_files *files, char *limiter, int file)
{
	char	*line;

	while (1)
	{
		write(1, "pipe heredoc>", 14);
		line = get_next_line(0);
		if (!line)
			exit(EXIT_FAILURE);
		if (!ft_strncmp(limiter, line, ft_strlen(limiter) + 1))
		{
			free(line);
			break ;
		}
		write (file, line, ft_strlen(line));
		free(line);
	}
}

void	here_doc_open(t_files *files, char *limiter)
{
	int		file;

	file = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file < 0)
		perror_and_exit("Open here_doc 1");
	here_doc_write(files, limiter, file);
	close(file);
	files->infile = open (".here_doc", O_RDONLY);
	if (files->infile < 0)
	{
		unlink(".here_doc");
		perror_and_exit("Open here_doc 2");
	}
}
