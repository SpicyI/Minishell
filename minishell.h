/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:54:11 by del-khay          #+#    #+#             */
/*   Updated: 2023/01/29 19:58:56 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
/*          includes        */
#include <stdio.h>
#include "libft/libft.h"
#include <dirent.h>

/*          defines         */
#define ECHO_NL "-n"

/*          structs         */
// contains the command table for now
// typedef struct s_cmds
// {
    
// } t_cmds;

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
#endif
