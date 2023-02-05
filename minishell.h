/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:54:11 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/06 00:16:18 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
/*          includes        */
#include <stdio.h>
#include "libft/libft.h"
#include <dirent.h>

/************************************************************************************************/
/*          defines         */
#define ECHO_NL "-n"
#define N_BUILTIN 7
#define FREE_FD_ARR 1
#define NO_FREE_FD_ARR 0





/************************************************************************************************/
/*          structs         */

typedef struct s_match{
	int (*sh_built)(char **);
	char *name;
} t_match;

// environnement variables
typedef struct s_env
{
	char *name;
	char *value;
	struct s_env	*next;
} t_env;

// for the export command
typedef struct s_export
{
	char *name;
	struct s_export	*next;
} t_export;
// for the env vars that are not in the env list but can be exporte through export 
typedef struct s_not_env
{
	char *name;
	char *value;
	struct s_not_env	*next;
} t_not_env;

// command
typedef struct s_cmd
{
	char **append;
	char **output;
	char **delimiter;
	char **input;
	char **cmd;
	int	last_in;
	int	last_out;
	int	is_built_in;
} t_cmd;

// cmd table
typedef struct s_cmds{
	t_cmd *line;
	int size;
} t_cmds;

//global struct
typedef struct s_line{
	int	exit;
	t_env *env;
    t_not_env *not_env;
    t_export *exp;
} t_line;

t_line g_gfl;








/**************************************************************************************************/
/*          echo            */
// all good do far
int    echo(char **str);
int is_option(char *str);

/*          cd              */
// handle OLDPWD and PWD env vars snd cd -
int    cd(char *path);

/*         pwd              */
//all good so far
int   pwd(void);

/*			export 			*/
int ft_env(char *str);
int	export_type(char **tab);
int exporter(char **tab);
int    importer(char *str);
int is_env(char **tab);
int is_export(char **tab);
int is_not_env(char **tab);
int	export(char **str);
void	printexport(void);
char	**ft_export_spliter(char *str);
int	check_name(char *name, int opt);
t_export	*ft_exportnew(char *content);
t_env	*ft_envnew(char **content);
void	ft_envadd_back(t_env **alst, t_env *new);
void	ft_exportadd_back(t_export **alst, t_export *new);
void	free_not_env_node(t_not_env *node);
void	free_env_node(t_env *node);
void	free_export_node(t_export *node);

/*			unset			*/
int unset_env(char *name);
int unset_export(char *name);
int unset_not_env(char *name);
int    unset(char **args);

/*			env				*/
int    env(char **args);

/*			exit			*/
int    shell_exit(char **args);
#endif
