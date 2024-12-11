/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 05:56:26 by mboughra          #+#    #+#             */
/*   Updated: 2024/12/11 13:01:33 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, FORK);
	if (philo->data->num == 1)
	{
		ft_usleep(philo->data->dietime, philo);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, FORK);
	print_status(philo, EAT);
	pthread_mutex_lock(philo->data->action);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->data->action);
	ft_usleep(philo->data->eatime, philo);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	print_status(t_philo *philo, int status)
{
	long long	time;

	time = get_current_time() - philo->data->start_time;
	pthread_mutex_lock(philo->data->write);
	if (status == DEAD)
		printf("%lld %d %s\n", time, philo->id, "died");
	else if ((status == FORK) && !check_death(philo))
		printf("%lld %d %s\n", time, philo->id, "has taken a fork");
	else if ((status == THINK) && !check_death(philo))
		printf("%lld %d %s\n", time, philo->id, "is thinking");
	else if ((status == SLEEP) && !check_death(philo))
		printf("%lld %d %s\n", time, philo->id, "is sleeping");
	else if ((status == EAT) && !check_death(philo))
		printf("%lld %d %s\n", time, philo->id, "is eating");
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
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
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
		ft_usleep(philo->data->eatime / 4, philo);
	while (1)
	{
		if (check_death(philo))
			return (NULL);
		print_status(philo, THINK);
		eat(philo);
		print_status(philo, SLEEP);
		ft_usleep(philo->data->sleeptime, philo);
	}
	return (NULL);
}

long long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
