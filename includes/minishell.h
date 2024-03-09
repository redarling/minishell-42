/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:34:28 by imehdid           #+#    #+#             */
/*   Updated: 2024/03/09 16:00:20 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define CLEAR_SCREEN "\033[2J\033[H"

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <curses.h>
# include <termcap.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <sys/wait.h>
# include "pipeline.h"

typedef enum s_nodetype
{
	COMMAND_NODE,
	PIPE_NODE,
	UNRECOGNIZED_NODE
}	t_nodetype;

typedef struct s_astnode
{
	t_nodetype			type;
	char				*value;
	struct s_astnode	*left;
	struct s_astnode	*right;
	int					*quotes_indexes;
}	t_astnode;

typedef struct s_list
{
	char							*content;
	struct s_list					*next;
}	t_list;

//---------------------========================
void			program_exit(int code);
int				handle_commands(char *input);
void			handle_signals(void);

//-------Execution-------========================
int				init_executor(t_astnode *root, t_list **env);
int				execute_pipeline(char **cmds, t_list **env, t_astnode *root);
void	launch_executable(char *cmd, char **envp);

//-------Execution utils-------==================
char			*get_path(char *cmd, char *path_full);
void			close_pipe_fds(int *fd, int size);
t_pipeline		get_pipe_utils(char **cmds);
void			launch_cmd(char *cmd, char **envp);
char			*pipes_validation(char *input);
void			not_found(char *cmd);
//-------Env utils-------========================
void free_list(t_list **env);
char **create_envp(t_list *env);
int	ft_lstsize(t_list *lst);
//-------Built-ins-------========================
int				handle_builtin(char *input, char **envp, t_list **env, t_astnode *root);
int				execute_echo(char *arg);
int				execute_pwd(void);
int				execute_export(char *arg, t_list *env, char **envp);
int				execute_env(char **envp);
void			execute_exit(char *input, t_list **env, t_astnode *root, char **envp);
int				execute_cd(char *path, t_list **env);
int				execute_unset(t_list **head, char *key);
int				update_old_pwd_dir(t_list **env); // cd utils
int				update_pwd(t_list **env); // cd utils_two

//-------Parsing-------========================
t_astnode		*parsing(char **input);
t_astnode		*init_ast(char **elements);
t_astnode		*create_node(char *element);
enum s_nodetype	get_element_type(char *element);
int				syntax_checker(t_astnode *root);
char			*pipes_validation(char *input);
int				quotes_validation(char **elements);
//----Split elements---========================
char			**split_quotes(char *input, char *skip);
//-------Utils---------========================
void			skip_quotes(char *input, int *i);
int				count_words(char *input, char *skip);
char			*malloc_word(char *input, int *i, char *skip);
void			copy_word(char *result, char *input, int *i, char *skip);
int				size_double_array(char **array);
//---------------------========================

//----Parsing utils----========================
void			free_double_array(char **array);
void			free_all_nodes(t_astnode *root);
int				ft_strcmp(char *one, char *two);
int				contain_str(char **array, char *element);
void			skip_quotes(char *input, int *i);
//---------------------========================

#endif
