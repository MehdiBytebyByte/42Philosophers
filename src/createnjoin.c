/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 02:28:22 by mboughra          #+#    #+#             */
/*   Updated: 2024/12/08 16:22:15 by mboughra         ###   ########.fr       */
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

static void	no_meals(t_philo *philo)
{
	t_philo *tmp;
	
	tmp = philo;
	while (tmp)
	{
		tmp->last_meal = get_current_time();
		tmp = tmp->next;
	}
	tmp = philo;
	while (1)
	{
		pthread_mutex_lock(tmp->data->action);
		if((get_current_time() - tmp->last_meal ) > tmp->data->dietime)
		{
			tmp->data->dead = 1;
			pthread_mutex_unlock(tmp->data->action);
			print_status(tmp, "died");
			break;
		}
		pthread_mutex_unlock(tmp->data->action);
		if (tmp->next == NULL)
			tmp = philo;
		else
			tmp = tmp->next;
	}
}

static void meals(t_philo *philo)
{
	t_philo *tmp;
	
	tmp = philo;
	while (tmp)
	{
		tmp->last_meal = get_current_time();
		tmp = tmp->next;
	}
	tmp = philo;
	while (1)
	{
		pthread_mutex_lock(tmp->data->action);
		if((get_current_time() - tmp->last_meal ) > tmp->data->dietime)
		{
			tmp->data->dead = 1;
			pthread_mutex_unlock(tmp->data->action);
			print_status(tmp, "died");
			break;
		}
		if(philo->meals_eaten > philo->data->meals)
		{
			tmp->data->dead = 1;
			pthread_mutex_unlock(tmp->data->action);
			break;
		}
		pthread_mutex_unlock(tmp->data->action);
		if (tmp->next == NULL)
			tmp = philo;
		else
			tmp = tmp->next;
	}
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
	if (!flag)
		no_meals(philo);
	else
	{
		meals(philo);
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