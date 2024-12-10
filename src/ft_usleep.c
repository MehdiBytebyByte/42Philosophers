/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:13:00 by mboughra          #+#    #+#             */
/*   Updated: 2024/12/08 15:20:59 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"




void ft_usleep(long time, t_philo *philo)
{
	unsigned long long old;

	old = get_current_time();
	while (get_current_time() - old <= time)
	{
		pthread_mutex_lock(philo->data->action);
		if (philo->data->dead)
		{
			pthread_mutex_unlock(philo->data->action);  //that
			return ;
		}
		pthread_mutex_unlock(philo->data->action);  //that
		usleep(10);
	}
}
// void ft_usleep(long time, t_philo *philo)
// {
// 	long old = get_current_time();

// 	while (get_current_time() - old <= time)
// 	{ 
// 		pthread_mutex_lock(philo->data->action); //that
// 		if ((get_current_time() - philo->last_meal) > philo->data->dietime)
// 		{
// 			pthread_mutex_unlock(philo->data->action); //that
// 			print_status(philo, "died");
// 			pthread_mutex_lock(philo->data->action);  // this
// 			philo->finished  = 1;
// 			philo->data->dead = 1;
// 			pthread_mutex_unlock(philo->data->action); // this
// 			return ;
// 		}
// 		pthread_mutex_unlock(philo->data->action);  //that
// 		usleep(100);
// 	}
// }