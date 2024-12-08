/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 05:56:26 by mboughra          #+#    #+#             */
/*   Updated: 2024/12/08 16:20:19 by mboughra         ###   ########.fr       */
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
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->data->action);
	ft_usleep(philo->data->eatime, philo);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

#include <string.h>

void print_status(t_philo *philo, char *status)
{
	long long current_time;
	
	current_time = get_current_time() - philo->data->start_time;
	if (strcmp(status, "died") == 0)
	{
		printf("%lld %d %s\n", current_time, philo->id, status);
		return ;
	}
	if (!check_death(philo))
	{
		pthread_mutex_lock(philo->data->write);
		printf("%lld %d %s\n", current_time, philo->id, status);
		pthread_mutex_unlock(philo->data->write);
	}
	
}

bool	check_death(t_philo	*philo)
{
	pthread_mutex_lock(philo->data->action);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(philo->data->action);
		// print_status(philo, "died");
		return (true);
	}
	pthread_mutex_unlock(philo->data->action);
	return (false);
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(philo->data->action);
		if(philo->data->start_time)
		{
			pthread_mutex_unlock(philo->data->action);
			break ;
		}
		pthread_mutex_unlock(philo->data->action);
	}
	// philo->last_meal = get_current_time();
	if (philo->id % 2 == 0)
	{
		ft_usleep(philo->data->eatime / 2, philo);
	}
	while (1)
	{
		if (check_death(philo))
			return (NULL);
		else
		{
			print_status(philo, "is thinking");
			eat(philo);
			if (check_death(philo))
				return (NULL);
			print_status(philo, "is sleeping");
			ft_usleep(philo->data->sleeptime, philo);
			if (check_death(philo))
				return (NULL);
		}
	}
	return (NULL);
}


long long get_current_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}