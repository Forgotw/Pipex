/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:52:00 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/07/02 15:08:23 by lsohler          ###   ########.fr       */
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
# endif

typedef struct s_list
{
	char			**cmd;
	char			*path;
	pid_t			pid;
	struct s_list	*next;
	struct s_list	*prev;
}				t_list;

typedef struct t_list
{
	int				heredoc;
	int				infile;
	int				outfile;
	pid_t			pid;
	int				open;
}				t_files;

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
t_list	*pipex_lstnew(int ac, char **av, int i, char **envp);
t_list	*pipex_parse(int ac, char **av, char **envp, t_files *files);
void	free_pipex_struct(t_list **list);
void	free_split(char **array);
t_files	*open_files(int ac, char **av);
void	pipex_child(t_list **child, t_files **file, char **envp);
void	perror_and_exit(char *error);
void	cmd_error(t_list **list, char *cmd);
void	execute_commands(t_list **child, t_files *files, char **envp);
void	here_doc_open(t_files *files, char *limiter);
void	here_doc_checker(char **av, t_files *files);

#endif