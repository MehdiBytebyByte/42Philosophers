/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 00:36:29 by mboughra          #+#    #+#             */
/*   Updated: 2024/12/11 11:44:47 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	ft_ofchercker(long max, long re, int s)
{
	if (max > re && s > 0)
		return (-1);
	if (max > re && s < 0)
		return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		s;
	long	re;
	long	max;

	i = 0;
	s = 1;
	re = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		max = re;
		re = re * 10 +(str[i] - 48);
		if (ft_ofchercker(max, re, s) != 1)
			return (ft_ofchercker(max, re, s));
		i++;
	}
	return (re * s);
}

int	ft_strcmp(char	*s1, char	*s2)
{
	size_t			i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
