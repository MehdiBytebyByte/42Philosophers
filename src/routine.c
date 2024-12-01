/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 05:56:26 by mboughra          #+#    #+#             */
/*   Updated: 2024/12/01 11:45:04 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <stdbool.h>



void	eat(t_philo *philo)
{
	// printf("")
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	philo->last_meal = get_current_time();
	// printf("last_meal = %lld\n", philo->last_meal);
	usleep(philo->data->eatime * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}



void	withoutflag(void	*arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
		{
			print_status(philo, "is thinking"); 
			if (((get_current_time() - philo->last_meal ) > philo->data->dietime) || philo->data->dead)
			{
				print_status(philo, "died");
				// add mutex here
				pthread_mutex_lock(philo->data->action);
				philo->data->dead = true;
				pthread_mutex_unlock(philo->data->action);
				break ;
			}
			eat(philo);
			print_status(philo, "is sleeping");
			usleep(philo->data->sleeptime * 1000);
		}
}
void	withflag(void	*arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (philo->meals_eaten < philo->data->meals)
	{
		print_status(philo, "is thinking");
		if (((get_current_time() - philo->last_meal ) > philo->data->dietime) || philo->data->dead)
		{
			print_status(philo, "died");
			pthread_mutex_lock(philo->data->action);
			philo->data->dead = true;
			pthread_mutex_unlock(philo->data->action);
			break ;
		}
		eat(philo);
		philo->meals_eaten++;
		print_status(philo, "is sleeping");
		usleep(philo->data->sleeptime * 1000);
	}
}




void	*routine(void *arg)
{
	t_philo *philo;
	bool	flag;
	
	philo = (t_philo *)arg;
	if (philo->data->meals == -1)
		flag = false;
	else
		flag = true;
	if (philo->id % 2 == 0)
	{
		// we can use a mutex here
		print_status(philo, "is thinking");
		usleep(philo->data->eatime * 1000);
	}
	philo->last_meal = get_current_time();
	if (!flag)
		withoutflag(arg);
	else
		withflag(arg);
return (NULL);
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

long long get_current_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}