/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:54:11 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/11 22:50:11 by del-khay         ###   ########.fr       */
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
#include <signal.h>
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

# define EXIT_NUM "minishell: exit: %s: numeric argument required\n"
# define EXIT_MANY "minishell: exit: too many arguments\n"
# define UNVALID_ID "minishell: export: `%s': not a valid identifier\n"
# define UNVALID_ID_SET "minishell: unset: %s: not a valid identifier\n"
# define NO_SUCH_FILE "minishell: %s: No such file or directory\n"
# define PERMISSION_DENIED "minishell: %s: Permission denied\n"
# define COMMAND_NOT_FOUND "minishell: %s: command not found\n"
# define NOT_A_DIRECTORY "minishell: %s: Not a directory\n"

/******************************************************/
/*          echo            */
int			echo(char **str);
int			is_option(char *str);

/*          cd              */
// handle  cd -
int			cd(char **path);

/*         pwd              */
int			pwd(void);

/*			export 			*/
int			ft_env(char *str);
int			export_type(char **tab);
int			exporter(char **tab);
int			importer(char *str);
int			is_env(char **tab);
int			is_export(char **tab);
int			is_not_env(char **tab);
int			export(char **str);
void		printexport(void);
char		**ft_export_spliter(char *str);
int			check_name(char *name, int opt);
t_export	*ft_exportnew(char *content);
t_env		*ft_envnew(char **content);
void		ft_envadd_back(t_env **alst, t_env *new);
void		ft_exportadd_back(t_export **alst, t_export *new);
void	ft_not_envadd_back(t_not_env **alst, t_not_env *new);
t_not_env	*ft_not_envnew(char **content);
void		free_not_env_node(t_not_env *node);
void		free_env_node(t_env *node);
void		free_export_node(t_export *node);
void sender(t_cmd *cmd);

/*			unset			*/
int			unset_env(char *name);
int			unset_export(char *name);
int			unset_not_env(char *name);
int			unset(char **args);

/*			env				*/
int			env(void);

/*			exit			*/
int			shell_exit(char **args);
int has_shell_var(char **str);
void shell_env_set(t_cmd *cmd, int cmd_n);
/***************************************************/
//this part is for the execution of the commands
/*              cmd analyzing       */
void ft_clean_cmd(t_cmd *cmd, int n);
/*  innit ref to builtins functs */
t_match		*init(void);
int			ft_envlen(t_env *env);
char		*ft_getenv(char *name);
char		**env_to_arr(void);
char		*getpath(char *cmd, char **path);
char		*check_abs_path(char *cmd);
int			ft_exitstatus(int status);
void		ft_isdir(char *cmd, int opt);
void		cmd_error(char *cmd);
int			ft_dprintf(char *format, char *str);

/*				herdoc		*/
int			herdoc(char *delmiter, int opt);
int			*init_herdocs(t_cmd *cmds, int num_of_cmds);

/*				closer.c*/
void		close_fds(int *fds, int i, int opt);
int			closer(t_cmd *cmd, int *input_fds, int *output_fds);
int			close_pipeline(t_built *utils, pid_t *id, int *herdocs);

/*				opener.c */
int			open_herdoc(t_cmd *cmd);
int			openinputs(char **in_files);
int			openoutputs(t_cmd *cmd);
int			openoutputs_trunc(t_cmd *cmd);
int			openoutputs_append(t_cmd *cmd);
int			opener(t_cmd *cmd, t_built *utils);

/*				execution 	*/
void		executor(t_cmds *cmds);
int			builtin(t_cmd *cmd, int opt);
void		unsetfds(t_built *utils);
void		setfds(t_built *utils, t_cmd *cmd, int opt);
int			pipeline(t_cmd *cmds, int num_of_cmds);
void		ft_waitall(pid_t *id, int num_of_cmds);
void		child_process(t_cmd *cmds, t_built *utils, int *herdocs, int i);

/*				single_cmd*/
void		ft_execve(t_cmd *cmd, int opt);
int			single_cmd(t_cmd *cmd);

/*                  redirections                */
void		set_last(t_built *utils, t_cmd *cmd);
void		set_first(t_built *utils, t_cmd *cmd);
void		set_middle(t_built *utils, t_cmd *cmd);
void		default_set(t_built *utils, t_cmd *cmd);
void		pipe_set(t_built *utils, t_cmd *cmd);
/*                  signals             */
void	sigint_handler(int sig);
#endif
