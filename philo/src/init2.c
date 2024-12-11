/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:29:25 by mboughra          #+#    #+#             */
/*   Updated: 2024/12/02 15:30:14 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_philo	*ft_lstnew(int id)
{
	t_philo	*e1;

	e1 = (t_philo *)galloc(sizeof(t_philo), 'a');
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
