/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 00:20:47 by mboughra          #+#    #+#             */
/*   Updated: 2024/11/19 18:53:22 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
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

void	print_philo(t_philo *philo)
{
	t_philo	*current;
	int		i;

	i = 0;
	current = philo;
	while (i < current->data->num)
	{
		printf("id = %d\n", current->id);
		i++;
		current = current->next;
	}
}
t_philo	*initmutix(t_data *data, t_philo *philo)
{
	pthread_mutex_t	*forks;
	t_philo			*current;
	int				i;
	
	forks = malloc(sizeof(pthread_mutex_t) * data->num);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < data->num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	current = philo;
	i = 1;
	while (i <= data->num)
	{
		current->left_fork = &forks[i - 1];
		if (i == data->num)
			current->right_fork = &forks[0];
		else
			current->right_fork = &forks[i];
		current = current->next;
		i++;
	}
	return (philo);
}


t_philo *create_threads(t_philo *philo)
{
	t_philo *current;

	current = philo;
	while (current)
	{
		pthread_create(&current->thread, NULL, &routine,(void *)current);
		current = current->next;
	}
	return (philo);
}

t_philo	*join_threads(t_philo *philo)
{
	t_philo *current;
	int i;

	i = 0;
	current = philo;
	while (current)
	{
		pthread_join(current->thread, NULL);
		current = current->next;
	}return (philo);
}

t_philo *all_init(t_data *data, t_philo *philo)
{
	philo = initallphilos(data);
	if (!philo)
		return (NULL);
	philo = initmutix(data, philo);
	if (!philo)
		return (NULL);
	return (philo);
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




int main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philo;

	data = malloc(sizeof(t_data));
	if (!data)
		return (write(2, "MALLOC FAILLED\n", 16), 1);
	if (parse(ac, av, data))
		return (1);
	// print_data(data);
	philo = all_init(data, philo);
	if (!philo)
		return (write(2, "MALLOC FAILLED\n", 16), 1);
	data->write = malloc(sizeof(pthread_mutex_t));
	if (!data->write)
		return (write(2, "MALLOC FAILLED\n", 16), 1);
	pthread_mutex_init(data->write, NULL);
	// print_info(philo, data);
	create_threads(philo);
	join_threads(philo);
	pthread_mutex_destroy(data->write);
	return (0);
}
