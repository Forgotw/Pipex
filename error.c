/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler@student.42.fr <lsohler>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:10:04 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/05/20 15:48:01 by lsohler@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	perror_and_exit(char *error)
{
	perror(error);
	exit(EXIT_FAILURE);
}

void	cmd_error(px_list **list, char *cmd)
{
	write(2, "Command not found: ", 20);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
	//free_pipex_struct(list);
	exit(EXIT_FAILURE);
}