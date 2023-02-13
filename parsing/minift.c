/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minift.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:26:02 by azakariy          #+#    #+#             */
/*   Updated: 2023/02/13 23:52:22 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_line(int nl, char *line)
{
	char	*line2;

		if (nl)
			line2 = ft_clean_join(line, ft_trim(ft_color(0), " "));
		else
			line2 = ft_trim(ft_color(1), " ");
	if (!line2)
		exit(0);
	return(line2);
}
