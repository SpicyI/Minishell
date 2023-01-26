/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:39:10 by del-khay          #+#    #+#             */
/*   Updated: 2022/12/22 16:46:27 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	char	*spcs;

	spcs = " \t\n\v\f\r";
	while (*spcs)
	{
		if (c == *spcs)
			return (1);
		spcs++;
	}
	return (0);
}

static	void	checkmaxmin(long n)
{
	if (n < INT_MIN || n > INT_MAX)
	{
		ft_putendl_fd("Error", 2);
		exit (1);
	}
}

int	ft_atoi(const char *nptr)
{
	int					s;
	unsigned long long	rslt;

	s = 1;
	rslt = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			s *= -1;
		nptr++;
	}
	while (*nptr > 47 && *nptr < 58)
	{
		rslt = rslt * 10 + (*nptr - '0');
		nptr++;
	}
	checkmaxmin(s * rslt);
	if (rslt < LONGMAX)
		return (s * rslt);
	else if (s > 0)
		return (-1);
	return (0);
}
