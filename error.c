/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:10:04 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/07/02 15:31:02 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	perror_and_exit(char *error)
{
	perror(error);
	exit(EXIT_FAILURE);
}

void	cmd_error(t_list **list, char *cmd)
{
	write(2, "command not found: ", 20);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
	free_pipex_struct(list);
	exit(EXIT_FAILURE);
}
