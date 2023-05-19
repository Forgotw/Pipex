/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler@student.42.fr <lsohler>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:59:21 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/05/12 11:42:06 by lsohler@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*void	my_dup2(px_list *child)
{
		dup2();
		dup2();
		close();
}*/
void	redir_child(px_list *current, f_list *files, int *pipefd, int prev_pipe_in)
{
	if (current->prev == NULL) // First command
	{
		dup2(files->infile, STDIN_FILENO);
	}
	else
	{
		dup2(prev_pipe_in, STDIN_FILENO);
		close(prev_pipe_in);
	}
	if (current->next) // Not the last command
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		}
	else
	{
		dup2(files->outfile, STDOUT_FILENO);
	}
}

void	execute_commands(px_list **child, f_list *files, char **envp)
{
	int pipefd[2];
	int status;
	int prev_pipe_in = -1;
	pid_t wpid;
	px_list *tmp;

	tmp = *child;
	while (tmp)
	{
		if (tmp->next)
		{
			if (pipe(pipefd) < 0)
				perror_and_exit("pipe");
		}
		tmp->pid = fork();
		if (tmp->pid < 0)
			perror_and_exit("fork");
		if (tmp->pid == 0)
		{
			redir_child(tmp, files, pipefd, prev_pipe_in);
			if (execve(tmp->path, tmp->cmd, envp) < 0)
				perror_and_exit("execve");
		}
		else
		{
			if (prev_pipe_in != -1)
				close(prev_pipe_in);
			if (tmp->next)
			{
				prev_pipe_in = pipefd[0];
				close(pipefd[1]);
			}
		}
		tmp = tmp->next;
	}
	while ((wpid = wait(&status)) > 0);
}

void	pipex_child(px_list **child, f_list **file, char **envp)
{
	//printf("test\n");
	if ((*child)->child_n == 1)
	{
		dup2((*file)->infile, 0);
		dup2((*child)->fd[1], 1);
		close((*child)->fd[0]);
	}
	else if ((*child)->child_n == -1)
	{
		//printf("testlast\n");
		dup2((*child)->prev->fd[0], 0);
		dup2((*file)->outfile, 1);
	}
	else
	{
		dup2((*child)->prev->fd[0], 0);
		dup2((*child)->fd[1], 1);
		close((*child)->fd[0]);
	}
	execve((*child)->path, (*child)->cmd, envp);
}
