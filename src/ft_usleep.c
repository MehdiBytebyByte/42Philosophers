/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:13:00 by mboughra          #+#    #+#             */
/*   Updated: 2024/12/02 09:28:06 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"




void ft_usleep(long time)
{
	long old = get_current_time();

	while (get_current_time() - old <= time)
	{
		usleep(100);
	}
}