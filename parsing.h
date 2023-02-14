/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 14:57:02 by azakariy          #+#    #+#             */
/*   Updated: 2023/02/14 17:16:17 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H

# define PARSING_H
# include "libft/libft.h"
# include <dirent.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_wild
{
	struct dirent		*de;
	DIR					*dir;
}						t_wild;
typedef struct s_builtin
{
	int					input_fd;
	int					output_fd;
	int					herdoc_fd;
	int					status;
	int					cmd_num;
	int					default_fd[2];
	int					b_pipe[2];
}						t_built;

typedef struct s_match
{
	int					(*sh_built)(char **);
	char				*name;
}						t_match;

// environnement variables
typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
}						t_env;

// for the export command
typedef struct s_export
{
	char				*name;
	struct s_export		*next;
}						t_export;
// for the env vars that are not in the env list
// but can be exporte through export
typedef struct s_not_env
{
	char				*name;
	char				*value;
	struct s_not_env	*next;
}						t_not_env;

// command
typedef struct s_cmd
{
	char				**append;
	char				**output;
	char				**delimiter;
	char				**input;
	char				**cmd;
	int					last_in;
	int					last_out;
	int					is_built_in;
}						t_cmd;

// cmd table
typedef struct s_cmds
{
	t_cmd				*line;
	int					size;
}						t_cmds;

//global struct
typedef struct s_line
{
	int					exit;
	t_env				*env;
	t_not_env			*not_env;
	t_export			*exp;
	int					syntax_error;
	char				*pipeline_error;
	int					p_error_index;
	pid_t				*pid;
	int					crp;
}						t_line;

t_line					g_gfl;
// typedef struct s_env
// {
// 	char	*name;
// 	char	*value;
// 	void	*next;
// }	t_env;

// typedef struct s_not_env
// {
// 	char				*name;
// 	char				*value;
// 	struct s_not_env	*next;
// }	t_not_env;

// typedef struct s_cmd
// {
// 	char	**append;
// 	char	**output;
// 	char	**delimiter;
// 	char	**input;
// 	char	**cmd;
// 	int		last_in;
// 	int		last_out;
// 	int		is_built_in;
// }	t_cmd;

// typedef struct s_cmds{
// 	t_cmd	*line;
// 	int		size;
// }	t_cmds;

// typedef struct s_line{
// 	int			exit;
// 	t_env		*env;
// 	t_not_env	*not_env;
// 	int			syntax_error; // false by default
// 	char		*pipeline_error;
// 	int			p_error_index; // -1 by default
// }	t_line;

// t_line	g_gfl;

void					ft_butcher(char *line, char **cmds, char c);
int						ft_count_cmds(char *line, char c, int i);
char					**ft_super_split(char *line, char c);
void					ft_free_double(char **array);
char					***ft_double_spit(char *line, t_cmds *cmds_list);
void					ft_printf_double(char **array);
void					ft_prod_line(char **cmd, t_cmd *s_cmd, int is_last);
char					**ft_filter(char *part, int i);
int						ft_key_chars(char *str);
char					**ft_append(char **array, char *new_str);
int						ft_valid_syntax(char **cmd, int i, int is_last);
void					ft_throw_error(char *str, int code);
void					ft_right_arrow(char **cmd, int i, int is_last);
void					ft_left_arrow(char **cmd, int i, int is_last);
int						ft_strcmp(char *str, char *str2);
void					ft_fill_struct(char **array, t_cmd *cmd, int i,
							int is_last);
void					ft_print_struct(t_cmd *cmd);
void					ft_init_struct(t_cmd *cmd);
char					**ft_destructor(char **array, char **array2, int j);
void					ft_pipeline_error(char *line, int i, int nbr);
char					*ft_append_char(char *str, char c);
char					*ft_get_env(char *str, int i);
char					*ft_replace_env(char *str, int i, int in_d, int in_s);
void					ft_find_env(char **array);
t_env					*ft_link(char **envp);
t_env					*ft_new_env(char *name, char *value);
void					ft_env_add(t_env **lst, t_env *new);
void					ft_open_doc(t_cmd *line, int i);
char					*ft_remove_quotes(char *str);
int						ft_skip(char *line, int i, char c);
void					ft_init_global(char **envp);
void					ft_reset(char *line, t_cmds *cmds, int nl);
t_cmds					*ft_parsing(char *line, int i);
void					ft_pipe_syntax(char *line, int i);
void					ft_doc_doc(t_cmd *line, int i);
char					**ft_split_by_pipeline(char *line);
int						ft_pipe_counter(char *line);
void					ft_set_helpers(char **array, t_cmd *cmd);
char					*ft_trim(char *line, char *set);
char					*ft_clean_join(char *str, char *str2);
void					ft_free_struct(t_cmds *cmds);
char					*ft_color(int i);
void					ft_read_loop(int nl, char *line, t_cmds *cmds);
t_env					*ft_no_env(void);
char					*ft_find_not_env(char *name);
char					*ft_hyphen(char *str);
void					*ft_collect(int size, int nbr);
char					*ft_get_line(int nb, char *line);
int						ft_skip_quotes(char *str, int i);

#endif