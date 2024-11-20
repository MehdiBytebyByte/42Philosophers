/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 00:18:39 by mboughra          #+#    #+#             */
/*   Updated: 2024/11/19 18:49:14 by mboughra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_data
{
	int				num;
	int				dietime;
	int				eatime;
	int				sleeptime;
	int				meals;
	long long		start_time;
	bool			someonedied;
	pthread_mutex_t	*write;
}	t_data;
typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal;
	t_data			*data;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	bool			is_eating;
	bool			is_sleeping;
	bool			is_thinking;
	bool			is_dead;
	struct s_philo	*next;
}	t_philo;

//**tools**//
int			ft_atoi(const char *str);
int			parse(int ac, char **av, t_data *data);
int			parsechar(char *str);
int			ft_isdigitplusplus(char *str);
t_philo		*initallphilos(t_data *data);
void		ft_lstadd_back(t_philo **lst, t_philo *new);
t_philo		*ft_lstnew(int id);
t_data		*setter(t_data *data, int i, int holder);
t_philo		*initmutix(t_data *data, t_philo *philo);
void		*routine(void	*arg);
void		print_status(t_philo *philo, char *status);
long long	get_current_time(void);
#endif