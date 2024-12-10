/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 03:41:07 by mboughra          #+#    #+#             */
/*   Updated: 2024/12/08 11:46:42 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	inithelper(t_philo	*current, int i, t_data	*data)
{
	while (i <= data->num)
	{
		current->finished = false;
		current->data = data;
		current->last_meal = 0;
		current->data->dead = false;
		current->meals_eaten = 0;
		current = current->next;
		i++;
	}
}

t_philo	*initallphilos(t_data *data)
{
	t_philo	*head;
	t_philo	*current;
	int		i;	

	data->start_time = 0;
	i = 1;
	head = ft_lstnew(1);
	if (!head)
		return (NULL);
	if (data->num != 1)
	{
		while (i < data->num)
		{
			current = ft_lstnew(i + 1);
			if (!current)
				return (NULL);
			ft_lstadd_back(&head, current);
			i++;
		}
		current->next = NULL;
		i = 1;
	}
	current = head;
	inithelper(current, i, data);
	return (head);
}

t_philo	*all_init(t_data *data, t_philo *philo)
{
	philo = initallphilos(data);
	if (!philo)
		return (NULL);
	philo = initmutix(data, philo);
	if (!philo)
		return (NULL);
	data->write = galloc(sizeof(pthread_mutex_t), 'a');
	if (!data->write)
		return (NULL);
	data->action = galloc(sizeof(pthread_mutex_t), 'a');
	if (!data->action)
		return (NULL);
	data->check_death = galloc(sizeof(pthread_mutex_t), 'a');
	if (!data->check_death)
		return (NULL);
	if (pthread_mutex_init(data->write, NULL) != 0
		|| pthread_mutex_init(data->action, NULL) != 0 
		|| pthread_mutex_init(data->check_death, NULL) != 0)
	{
		write(2, "MUTEX INIT FAILLED\n", 20);
		return (NULL);
	}
	return (philo);
}

t_philo	*initmutix(t_data *data, t_philo *philo)
{
	pthread_mutex_t	*forks;
	t_philo			*current;
	int				i;

	forks = galloc(sizeof(pthread_mutex_t) * data->num, 'a');
	if (!forks)
		return (NULL);
	i = 0;
	while (i < data->num)
		pthread_mutex_init(&forks[i++], NULL);
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
