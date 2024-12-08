/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:49:27 by mboughra          #+#    #+#             */
/*   Updated: 2024/12/08 11:15:04 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routineofone(void	*arg)
{
	t_data *data;
	t_philo	*philo;
	pthread_mutex_t mutix;

	pthread_mutex_init(&mutix, NULL);
	philo->id = 1;
	data = (t_data *)arg;
	print_status(philo, "is thinking");
	return (NULL);
}

void	one_philo(t_data	*data)
{
	pthread_t *philo;
	pthread_create(philo, NULL, &routineofone, (void *)data);
}
