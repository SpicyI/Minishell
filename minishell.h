/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:54:11 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/10 15:16:53 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
/*          includes        */
# include "libft/libft.h"
# include "parsing.h"
# include <dirent.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
/****************************************************************/
/*          defines         */
# define ECHO_NL "-n"
# define N_BUILTIN 7
# define FREE_FD_ARR 1
# define NO_FREE_FD_ARR 0
# define APPEND 1
# define TRUNC 2
# define HERDOC_ON 1
# define HERDOC_OFF 0
# define HERDOC_FD 1
# define INPUT_FD 2
/*       error     */

// #define
// #define
// #define
// #define
// #define

/**********************************************************/

/*          structs         */

// typedef struct s_builtin
// {
// 	int					input_fd;
// 	int					output_fd;
// 	int					herdoc_fd;
// 	int					status;
// 	int					default_fd[2];
// 	int					b_pipe[2];
// }						t_built;

// typedef struct s_match
// {
// 	int					(*sh_built)(char **);
// 	char				*name;
// }						t_match;

// // environnement variables
// typedef struct s_env
// {
// 	char				*name;
// 	char				*value;
// 	struct s_env		*next;
// }						t_env;

// // for the export command
// typedef struct s_export
// {
// 	char				*name;
// 	struct s_export		*next;
// }						t_export;
// // for the env vars that are not in the env list
// // but can be exporte through export
// typedef struct s_not_env
// {
// 	char				*name;
// 	char				*value;
// 	struct s_not_env	*next;
// }						t_not_env;

// // command
// typedef struct s_cmd
// {
// 	char				**append;
// 	char				**output;
// 	char				**delimiter;
// 	char				**input;
// 	char				**cmd;
// 	int					last_in;
// 	int					last_out;
// 	int					is_built_in;
// }						t_cmd;

// // cmd table
// typedef struct s_cmds
// {
// 	t_cmd				*line;
// 	int					size;
// }						t_cmds;

// //global struct
// typedef struct s_line
// {
// 	int					exit;
// 	t_env				*env;
// 	t_not_env			*not_env;
// 	t_export			*exp;
// 		int		syntax_error;
// 	char	*pipeline_error;
// 	int		p_error_index;
// }						t_line;

// t_line					g_gfl;

/******************************************************/
/*          echo            */
// all good do far
int						echo(char **str);
int						is_option(char *str);

/*          cd              */
// handle  cd - and cd a rmoved dir
int						cd(char **path);

/*         pwd              */
//all good so far
int						pwd(void);

/*			export 			*/
int						ft_env(char *str);
int						export_type(char **tab);
int						exporter(char **tab);
int						importer(char *str);
int						is_env(char **tab);
int						is_export(char **tab);
int						is_not_env(char **tab);
int						export(char **str);
void					printexport(void);
char					**ft_export_spliter(char *str);
int						check_name(char *name, int opt);
t_export				*ft_exportnew(char *content);
t_env					*ft_envnew(char **content);
void					ft_envadd_back(t_env **alst, t_env *new);
void					ft_exportadd_back(t_export **alst, t_export *new);
void					free_not_env_node(t_not_env *node);
void					free_env_node(t_env *node);
void					free_export_node(t_export *node);

/*			unset			*/
int						unset_env(char *name);
int						unset_export(char *name);
int						unset_not_env(char *name);
int						unset(char **args);

/*			env				*/
int						env(void);

/*			exit			*/
int						shell_exit(char **args);

/***************************************************/
//this part is for the execution of the commands
/*  innit ref to builtins functs */
t_match					*init(void);
int						ft_envlen(t_env *env);
char					*ft_getenv(char *name);
char					**env_to_arr(void);
char					*getpath(char *cmd, char **path);
char					*check_abs_path(char *cmd);
int						ft_exitstatus(int status);
void					ft_isdir(char *cmd, int opt);
/*				herdoc		*/
int						herdoc(char *delmiter, int opt);

/*				closer.c*/
void					close_fds(int *fds, int i, int opt);
int						closer(t_cmd *cmd, int *input_fds, int *output_fds);

/*				opener.c */
int						open_herdoc(t_cmd *cmd);
int						openinputs(char **in_files);
int						openoutputs(t_cmd *cmd);
int						openoutputs_trunc(t_cmd *cmd);
int						openoutputs_append(t_cmd *cmd);
int						opener(t_cmd *cmd, t_built *utils);

/*				execution 	*/
void					executor(t_cmds *cmds);
int						builtin(t_cmd *cmd);
void					unsetfds(t_built *utils);
void					setfds(t_built *utils, t_cmd *cmd, int  opt);
int						pipeline(t_cmd *cmds, int num_of_cmds);
void					ft_waitall(pid_t *id, int num_of_cmds);

/*				single_cmd*/
void					ft_execve(t_cmd *cmd, int opt);
int						single_cmd(t_cmd *cmd);
#endif
