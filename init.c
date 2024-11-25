/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 03:41:07 by mboughra          #+#    #+#             */
/*   Updated: 2024/11/25 00:07:50 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
