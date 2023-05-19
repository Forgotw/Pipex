/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler@student.42.fr <lsohler>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:10:04 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/05/12 11:43:58 by lsohler@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int		error_msg(char *msg)
{
	int	i;

	i = 0;
	while(msg[i])
		i++;
	write(STD_ERR, msg, i);
	return (-1);
}

void	perror_and_exit(char *error)
{
	perror(error);
	exit(EXIT_FAILURE);
}