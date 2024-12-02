/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 05:56:26 by mboughra          #+#    #+#             */
/*   Updated: 2024/12/02 15:12:47 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <stdbool.h>



void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	pthread_mutex_lock(philo->data->action);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(philo->data->action);
	ft_usleep(philo->data->eatime );
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void print_status(t_philo *philo, char *status)
{
	long long current_time;
	
	current_time = get_current_time() - philo->data->start_time;
	pthread_mutex_lock(philo->data->action);
	pthread_mutex_lock(philo->data->write);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(philo->data->action);
		pthread_mutex_unlock(philo->data->write);
		return ;
	}
	pthread_mutex_unlock(philo->data->action);
	printf("%lld %d %s\n", current_time, philo->id, status);
	pthread_mutex_unlock(philo->data->write);
}

bool	check_death(t_philo	*philo)
{
	pthread_mutex_lock(philo->data->action);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(philo->data->action);
		return (true);
	}
	pthread_mutex_unlock(philo->data->action);
	return (false);
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)  //we wait ta ybdaw kamlen
	{
		pthread_mutex_lock(philo->data->action);
		if (philo->data->start_time)
		{
			pthread_mutex_unlock(philo->data->action);
			break ;
		}
		pthread_mutex_unlock(philo->data->action);
	}
	if (philo->id % 2 == 0)
	{
		print_status(philo, "is thinking");
		ft_usleep(philo->data->eatime);
	}
	while (1)
	{
		pthread_mutex_lock(philo->data->action);
		if (philo->finished == 1)
			return (pthread_mutex_unlock(philo->data->action), (void *)0);
		pthread_mutex_unlock(philo->data->action);
		if (check_death(philo)) //check
			return (NULL);
		eat(philo);		//eat
		pthread_mutex_lock(philo->data->action);   // AAAA
		philo->meals_eaten++;
		pthread_mutex_unlock(philo->data->action); // AAAA
		if (check_death(philo)) //check
			return (NULL);
		print_status(philo, "is sleeping");
		ft_usleep(philo->data->sleeptime);
		print_status(philo, "is thinking");
	}
return (NULL);
}


long long get_current_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}