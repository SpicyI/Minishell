/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:15:34 by del-khay          #+#    #+#             */
/*   Updated: 2022/12/23 02:00:33 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "../libft.h"

char	*get_next_line(int fd);
char	*ft_fget(char *stash);
char	*ft_read_line(char *stash, int fd);
char	*ft_clean(char *stash);
int		is_nl(char *s);
#endif