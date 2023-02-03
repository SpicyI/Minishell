/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:54:11 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/03 22:44:34 by del-khay         ###   ########.fr       */
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








/************************************************************************************************/
/*          structs         */
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
	char *value;
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
void    echo(char **str);
int is_option(char *str);

/*          cd              */
// handle OLDPWD and PWD env vars snd cd -
void    cd(char *path);

/*         pwd              */
//all good so far
void   pwd(void);

/*			export 			*/
int	parss_export(char *str);
void	export(char **str);
void	printexport(void);
char	**ft_export_spliter(char *str);
int	check_name(char *name, int opt);
int	is_env(char **tab);
t_export	*ft_exportnew(char **content);
t_env	*ft_envnew(char **content);
void	ft_envadd_back(t_env **alst, t_env *new);
void	ft_exportadd_back(t_export **alst, t_export *new);
void	freenode2(t_not_env *node);
void	freenode(t_export *node);


#endif
