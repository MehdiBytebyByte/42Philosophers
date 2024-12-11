/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:52:33 by mboughra          #+#    #+#             */
/*   Updated: 2024/12/11 13:05:29 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	no_meals(t_philo *philo)
{
	t_philo	*tmp;

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
		if ((get_current_time() - tmp->last_meal) > tmp->data->dietime)
		{
			tmp->data->dead = 1;
			pthread_mutex_unlock(tmp->data->action);
			print_status(tmp, DEAD);
			break ;
		}
		pthread_mutex_unlock(tmp->data->action);
		if (tmp->next == NULL)
			tmp = philo;
		else
			tmp = tmp->next;
	}
}

static int	checkphilo(t_philo	*tmp)
{
	pthread_mutex_lock(tmp->data->action);
	if ((get_current_time() - tmp->last_meal) > tmp->data->dietime)
	{
		tmp->data->dead = 1;
		pthread_mutex_unlock(tmp->data->action);
		print_status(tmp, DEAD);
		return (1);
	}
	if (tmp->meals_eaten > tmp->data->meals && tmp->data->num != 1)
	{
		tmp->data->dead = 1;
		pthread_mutex_unlock(tmp->data->action);
		return (1);
	}
	pthread_mutex_unlock(tmp->data->action);
	return (0);
}

static void	meals(t_philo *philo)
{
	t_philo	*tmp;

	tmp = philo;
	while (tmp)
	{
		tmp->last_meal = get_current_time();
		tmp = tmp->next;
	}
	tmp = philo;
	while (1)
	{
		if (checkphilo(tmp))
			break ;
		if (tmp->next == NULL)
			tmp = philo;
		else
			tmp = tmp->next;
		usleep(100);
	}
}

int	monitor(t_philo *philo)
{
	int		flag;

	if (philo->data->meals != -1)
		flag = 1;
	else
		flag = 0;
	pthread_mutex_lock(philo->data->action);
	philo->data->start_time = get_current_time();
	pthread_mutex_unlock(philo->data->action);
	if (!flag)
		no_meals(philo);
	else
		meals(philo);
	return (0);
}
