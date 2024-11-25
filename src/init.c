/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 03:41:07 by mboughra          #+#    #+#             */
/*   Updated: 2024/11/25 02:32:41 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_philo	*ft_lstnew(int id)
{
	t_philo	*e1;

	e1 = (t_philo *)malloc(sizeof(t_philo));
	if (!e1)
		return (NULL);
	e1->id = id;
	e1->next = NULL;
	return (e1);
}

void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo	*current;

	if (!new || !lst)
		return ;
	current = *lst;
	if (!current)
	{
		*lst = new;
		return ;
	}
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

t_philo	*initallphilos(t_data *data)
{
	t_philo	*head;
	t_philo	*current;
	int		i;	

	i = 1;
	head = ft_lstnew(1);
	if (!head)
		return (NULL);
	while (i < data->num)
	{
		current = ft_lstnew(i + 1);  //we allocate here
		if (!current)
			return (NULL);
		ft_lstadd_back(&head, current);
		i++;
	}
	current->next = NULL;
	i = 1;
	current = head;
	while (i <= data->num)
	{
		current->data = data;
		current->last_meal = 0;
		current->data->dead = false;
		current = current->next;
		i++;
	}
	return (head);
}

t_philo *all_init(t_data *data, t_philo *philo)
{
	philo = initallphilos(data); // malloc philo linked list
	if (!philo)
		return (NULL);
	philo = initmutix(data, philo); // malloc mutix array
	if (!philo)
		return (NULL); // some malloc or init failed
	data->write = malloc(sizeof(pthread_mutex_t)); //malloc write mutix
		if (!data->write)
			return (NULL);
	if (pthread_mutex_init(data->write, NULL) != 0)
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
	
	forks = malloc(sizeof(pthread_mutex_t) * data->num);
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
