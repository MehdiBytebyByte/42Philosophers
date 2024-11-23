/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 05:56:26 by mboughra          #+#    #+#             */
/*   Updated: 2024/11/22 22:55:53 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdbool.h>



void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	philo->last_meal = (get_current_time() - philo->data->start_time);
	// printf("last_meal = %lld\n", philo->last_meal);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	usleep(philo->data->eatime * 1000);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int i;

	i = 0;
	philo = (t_philo *)arg;
	// printf("philo->data->init time = %lld\n", philo->data->start_time);
	while (philo->data->someonedied == false)
	{
		if (philo->id % 2 == 0)
		{
			usleep(philo->data->eatime * 1000);
			print_status(philo, "is thinking");
		}
		eat(philo);
		print_status(philo, "is sleeping");
		usleep(philo->data->sleeptime * 1000);
		print_status((philo), "is thinking");
		long long a = get_current_time() - philo->last_meal; 
		if (philo->data->dietime > 0 &&)
		{
			printf("data->dietime = %d\n", philo->data->dietime);
			printf("time since last meal = %lld\n", get_current_time() - philo->last_meal);
			philo->is_dead = true;
			print_status(philo, "dead");
			philo->data->someonedied = true;
		}
		i++;
	}
	return (NULL);
}

void print_status(t_philo *philo, char *status)
{
	long long current_time;
	
	current_time = get_current_time() - philo->data->start_time;
	pthread_mutex_lock(philo->data->write);
	printf("%lld %d %s\n", current_time, philo->id, status);
	pthread_mutex_unlock(philo->data->write);
}

long long get_current_time(void)
{
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}