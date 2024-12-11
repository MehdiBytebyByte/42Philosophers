/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbageco.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:40:19 by mboughra          #+#    #+#             */
/*   Updated: 2024/12/11 11:42:13 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	list_add(t_garbage **list, t_garbage *new_item)
{
	t_garbage	*last;

	if (!list || !new_item)
		return ;
	if (!(*list))
	{
		*list = new_item;
		return ;
	}
	last = *list;
	while (last->next)
		last = last->next;
	last->next = new_item;
	new_item->next = NULL;
}

static t_garbage	*make_node(void *ptr)
{
	t_garbage	*node;

	node = malloc(sizeof(t_garbage));
	if (node == NULL)
	{
		printf("malloc failled \n");
		return (NULL);
	}
	node->adr = ptr;
	node->next = NULL;
	return (node);
}

static void	clear_list(t_garbage	**head)
{
	t_garbage	*curr;
	t_garbage	*next;

	curr = *head;
	while (curr != NULL)
	{
		next = curr->next;
		free(curr->adr);
		curr->adr = NULL;
		curr = next;
	}
}

void	*galloc(size_t	size, int mode)
{
	static t_garbage	*tracker;
	t_garbage			*node;
	void				*ptr;

	ptr = NULL;
	if (mode == 'a')
	{
		ptr = malloc(size);
		if (!ptr)
		{
			galloc(0, 'f');
			return (NULL);
		}
		if (tracker == NULL)
			tracker = make_node(ptr);
		else
		{
			node = make_node(ptr);
			list_add(&tracker, node);
		}
	}
	else if (mode == 'f')
		clear_list(&tracker);
	return (ptr);
}
