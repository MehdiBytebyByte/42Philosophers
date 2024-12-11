/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 00:20:47 by mboughra          #+#    #+#             */
/*   Updated: 2024/12/11 12:00:27 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

static void	mutex_destroyer(t_data *data, t_philo *philo)
{
	pthread_mutex_destroy(data->action);
	pthread_mutex_destroy(data->write);
	while (philo)
	{
		pthread_mutex_destroy(philo->left_fork);
		philo = philo->next;
	}
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philo;

	philo = NULL;
	data = NULL;
	data = galloc(sizeof(t_data), 'a');
	if (!data)
	{
		galloc(0, 'f');
		return (write(2, "MALLOC FAILLED\n", 16), 1);
	}
	if (parse(ac, av, data))
		return (galloc(0, 'f'), 1);
	philo = all_init(data, philo);
	if (!philo)
		return (write(2, "Error\n", 7), galloc(0, 'f'), 1);
	if (create_threads(philo) == NULL)
		return (write(2, "Error\n", 7), galloc(0, 'f'), 1);
	monitor(philo);
	if (join_threads(philo) == NULL)
		return (write(2, "Error\n", 7), galloc(0, 'f'), 1);
	mutex_destroyer(data, philo);
	galloc(0, 'f');
	return (0);
}
