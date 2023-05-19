/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:52:00 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/05/19 16:57:56 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>

# define STD_IN 0
# define STD_OUT 1 
# define STD_ERR 2

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
#endif

typedef	struct	s_list
{
	char			**cmd;
	char			*path;
	pid_t			pid;
	struct	s_list	*next;
	struct	s_list	*prev;
}				px_list;

typedef	struct	t_list
{
	int				heredoc;
	int				infile;
	int				outfile;
	pid_t			pid;
	int				open;
}				f_list;

char	**ft_split(char *s, char c);
char	*ft_strdup(const char *s1);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t elementCount, size_t elementSize);
char	*ft_strchr(const char *string, int searchedChar );
char	*get_next_line(int fd);

char	**pipex_path_array(char **envp);
char	*pipex_path(char *cmd, char **envp);
px_list	*pipex_lstnew(int ac, char **av, int i, char **envp);
px_list	*pipex_parse(int ac, char **av, char **envp, f_list *files);
void	free_pipex_struct(px_list **list);
void 	free_split(char **array);
f_list	*open_files(int ac, char **av);
void	pipex_child(px_list **child, f_list **file, char **envp);
void	perror_and_exit(char *error);
void	execute_commands(px_list **child, f_list *files, char **envp);
void	here_doc_open(f_list **files, char *limiter);
void	here_doc_checker(char **av, f_list *files);







#endif