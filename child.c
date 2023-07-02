/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:59:21 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/07/02 14:16:05 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	redir_child(t_list *cur, t_files *files, int *pipefd, int prev_pipe_in)
{
	if (cur->prev == NULL)
		dup2(files->infile, STDIN_FILENO);
	else
	{
		dup2(prev_pipe_in, STDIN_FILENO);
		close(prev_pipe_in);
	}
	if (cur->next)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
	}
	else
		dup2(files->outfile, STDOUT_FILENO);
}

void	redir_prev_pipe_in(t_list *tmp, int *pipefd, int *prev_pipe_in)
{
	if (*prev_pipe_in != -1)
		close(*prev_pipe_in);
	if (tmp->next)
	{
		*prev_pipe_in = pipefd[0];
		close(pipefd[1]);
	}
}

void	fork_and_pipe(t_list **tmp, int *pipefd)
{
	if ((*tmp)->next)
		if (pipe(pipefd) < 0)
			perror_and_exit("pipe");
	(*tmp)->pid = fork();
	if ((*tmp)->pid < 0)
		perror_and_exit("fork");
}

void	execute_commands(t_list **child, t_files *files, char **envp)
{
	int		pipefd[2];
	int		status;
	int		prev_pipe_in;
	pid_t	wpid;
	t_list	*tmp;

	tmp = *child;
	prev_pipe_in = -1;
	while (tmp)
	{
		fork_and_pipe(&tmp, pipefd);
		if (tmp->pid == 0)
		{
			redir_child(tmp, files, pipefd, prev_pipe_in);
			if (execve(tmp->path, tmp->cmd, envp) < 0)
				perror_and_exit("execve");
		}
		else
			redir_prev_pipe_in(tmp, pipefd, &prev_pipe_in);
		tmp = tmp->next;
	}
	if (prev_pipe_in != -1)
		close(prev_pipe_in);
	while (wpid > 0)
		wpid = wait(&status);
}
