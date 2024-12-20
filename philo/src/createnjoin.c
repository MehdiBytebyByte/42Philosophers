/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 02:28:22 by mboughra          #+#    #+#             */
/*   Updated: 2024/12/11 13:58:35 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_philo	*create_threads(t_philo *philo)
{
	t_philo	*current;
	int		i;

	i = 0;
	current = philo;
	while (current)
	{
		i = pthread_create(&current->thread, NULL, &routine, (void *)current);
		if (i != 0)
			return (write(2, "THREAD CREATION FAILLED\n", 25), NULL);
		current = current->next;
	}
	return (philo);
}

t_philo	*join_threads(t_philo *philo)
{
	t_philo	*current;

	current = philo;
	while (current)
	{
		if (pthread_join(current->thread, NULL) != 0)
		{
			write(2, "THREAD JOIN FAILLED\n", 21);
			return (NULL);
		}
		current = current->next;
	}
	return (philo);
}
