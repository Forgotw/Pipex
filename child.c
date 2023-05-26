/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler@student.42.fr <lsohler>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:59:21 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/05/20 15:27:31 by lsohler@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	redir_child(px_list *cur, f_list *files, int *pipefd, int prev_pipe_in)
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

void	redir_prev_pipe_in(px_list *tmp, int *pipefd, int *prev_pipe_in)
{
	if (*prev_pipe_in != -1)
		close(*prev_pipe_in);
	if (tmp->next)
	{
		*prev_pipe_in = pipefd[0];
		close(pipefd[1]);
	}
}

void	fork_and_pipe(px_list **tmp, int *pipefd)
{
	if ((*tmp)->next)
		if (pipe(pipefd) < 0)
			perror_and_exit("pipe");
	(*tmp)->pid = fork();
	if ((*tmp)->pid < 0)
		perror_and_exit("fork");
}

void	execute_commands(px_list **child, f_list *files, char **envp)
{
	int		pipefd[2];
	int		status;
	int		prev_pipe_in;
	pid_t	wpid;
	px_list	*tmp;

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
