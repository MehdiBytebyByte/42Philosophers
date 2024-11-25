/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 00:20:47 by mboughra          #+#    #+#             */
/*   Updated: 2024/11/25 02:53:06 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <stdlib.h>

/* memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock */
void	print_data(t_data *data)
{
	printf("num = %d\n", data->num);
	printf("dietime = %d\n", data->dietime);
	printf("eatime = %d\n", data->eatime);
	printf("sleeptime = %d\n", data->sleeptime);
	printf("meals = %d\n", data->meals);
}

void print_info(t_philo *philo, t_data *data)
{
	t_philo *temp;
	temp = philo;
	printf("->%lld\n", data->start_time);
	while (temp)
	{
		printf("id = %d\n", temp->id);
		printf("mutix -> %p\n", temp->left_fork);
		printf("mutix -> %p\n", temp->right_fork);
		printf("====================================\n");
		temp = temp->next;
	}
}


void	f(){system("leaks Philosophers");}

void ifree(t_data *data, t_philo *philo)
{
	// TODO free all mallocs
}


int main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philo;

	// atexit(f);
	philo = NULL;
	data = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
		return (write(2, "MALLOC FAILLED\n", 16), 1);
	if (parse(ac, av, data))
		return (free(data), 1);
	philo = all_init(data, philo); // init data, philo, mutix
	if (!philo)
	{
		// malloc or init failed
		ifree(data, philo);
		return (write(2, "Error\n", 7), 1);
	}
	return (0);
	if (create_threads(philo) == NULL)
		{
			// thread creation failed
			ifree(data, philo);
			return (write(2, "Error\n", 7), 1);
		}
	if (join_threads(philo) == NULL)
	{
		// thread join failed
		ifree(data, philo);
		return (write(2, "Error\n", 7), 1);
	}
	ifree(data, philo);
	// function to free all mallocs and destroy all mutix
	return (0);
}
