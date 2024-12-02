/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 02:32:02 by mboughra          #+#    #+#             */
/*   Updated: 2024/12/02 15:49:20 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_isdigitplusplus(char *str)
{
	if (*str == '+')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int	parsechar(char *str)
{
	if (!ft_isdigitplusplus(str))
		return (1);
	return (0);
}

t_data	*setter(t_data *data, int i, int holder)
{
	if (i == 1)
		data->num = holder;
	if (i == 2)
		data->dietime = holder;
	if (i == 3)
		data->eatime = holder;
	if (i == 4)
		data->sleeptime = holder;
	if (i == 5)
		data->meals = holder;
	return (data);
}

int	parse2(int ac, char	**av, t_data *data)
{
	int	holder;
	int	i;

	i = 1;
	while (i != ac)
	{
		if (parsechar(av[i]))
			return (write(2, "INVALID PARAMETER(S)\n", 22), 1);
		else
		{
			holder = ft_atoi(av[i]);
			if (holder <= 0)
				return (write(2, "INVALID PARAMETER(S)\n", 22), 1);
			else
				data = setter(data, i, holder);
		}
		i++;
	}
	return (0);
}

int	parse(int ac, char **av, t_data *data)
{
	if (ac != 5 && ac != 6)
		return (write(2, "INVALID PARAMETER(S)\n", 22), 1);
	if (ac == 5)
		data->meals = -1;
	if (parse2(ac, av, data) == -1)
		return (-1);
	if (data->num < 1)
		return (write (2, "INVALID PARAMETER(S)\n", 22), 1);
	else if (data->num == 1)
	{
		one_philo(data);
	}
	return (0);
}
