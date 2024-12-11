/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:13:00 by mboughra          #+#    #+#             */
/*   Updated: 2024/12/11 12:57:34 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_usleep(long long time, t_philo *philo)
{
	long long	old;

	old = get_current_time();
	while (get_current_time() - old <= time)
	{
		pthread_mutex_lock(philo->data->action);
		if (philo->data->dead)
		{
			pthread_mutex_unlock(philo->data->action);
			return ;
		}
		pthread_mutex_unlock(philo->data->action);
		usleep(80);
	}
}
