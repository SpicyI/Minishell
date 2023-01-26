/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:54:11 by del-khay          #+#    #+#             */
/*   Updated: 2023/01/26 20:05:20 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
/*          includes        */
#include <stdio.h>
#include "libft/libft.h"
/*          defines         */
#define ECHO_NL "-n"



/*          echo            */
void    echo(char **str);
int arrlen(char **arr);
/*          cd              */

#endif
