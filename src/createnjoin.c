/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 02:28:22 by mboughra          #+#    #+#             */
/*   Updated: 2024/12/02 14:07:08 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_philo *create_threads(t_philo *philo)
{
	t_philo *current;

	current = philo;
	while (current)
	{
		if (pthread_create(&current->thread, NULL, &routine,(void *)current) == -1)
		{
			write(2, "THREAD CREATION FAILLED\n", 25);
			return (NULL);
		}
		current = current->next;
	}
	return (philo);
}

int	monitor(t_philo *philo)
{
	t_philo	*tmp;
	int		flag;

	if (philo->data->meals != -1)
		flag = 1;
	else
		flag = 0;
	tmp = philo;
	pthread_mutex_lock(philo->data->action);
	philo->data->start_time = get_current_time();
	pthread_mutex_unlock(philo->data->action);
	while (tmp)
	{
		tmp->last_meal = get_current_time();
		tmp = tmp->next;
	}
	while (1)
	{
		tmp = philo;
		pthread_mutex_lock(tmp->data->action); // AAAAAAA  (OPEN)
		if (((get_current_time() - philo->last_meal ) > philo->data->dietime))
		{
			pthread_mutex_unlock(tmp->data->action);   // AAAAAAA (CLOSE)
			print_status(philo, "died");
			pthread_mutex_lock(tmp->data->action); // BBBBBBB (OPEN)
			tmp->data->dead = 1;
			pthread_mutex_unlock(tmp->data->action); // BBBBBBB (CLOSE)
			break;
		}
		pthread_mutex_unlock(tmp->data->action); // AAAAAAA (CLOSE)]
		pthread_mutex_lock(tmp->data->action);	// CCCCCC (OPEN)
		if (flag && philo->data->meals == philo->meals_eaten)
		{
			philo->data->dead = 1;
			pthread_mutex_unlock(tmp->data->action);
			return (0);
		}
		pthread_mutex_unlock(tmp->data->action);	// CCCCCC (CLOSE)
		if (tmp->next == NULL)
			continue ;
		tmp = tmp->next;
	}
	
	return (0);
}

t_philo	*join_threads(t_philo *philo)
{
	t_philo *current;

	current = philo;
	while (current)
	{
		if (pthread_join(current->thread, NULL) == -1)
		{
			write(2, "THREAD JOIN FAILLED\n", 21);
			return (NULL);
		}
		current = current->next;
	}
	
	return (philo);
}