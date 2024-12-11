/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 00:18:39 by mboughra          #+#    #+#             */
/*   Updated: 2024/12/11 12:03:24 by mboughra         ###   ########.fr       */
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

# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DEAD 42

typedef struct s_garbage
{
	void				*adr;
	struct s_garbage	*next;
}	t_garbage;

typedef struct s_data
{
	int				num;
	int				dietime;
	int				eatime;
	int				sleeptime;
	int				meals;
	long long		start_time;
	bool			dead;
	pthread_mutex_t	*write;
	pthread_mutex_t	*action;
	pthread_mutex_t	*check_death;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	bool			finished;
	t_data			*data;
	struct s_philo	*next;
}	t_philo;

int			ft_atoi(const char *str);
int			parse(int ac, char **av, t_data *data);
t_philo		*initallphilos(t_data *data);
void		ft_lstadd_back(t_philo **lst, t_philo *new);
t_philo		*ft_lstnew(int id);
t_philo		*all_init(t_data *data, t_philo *philo);
t_philo		*initmutix(t_data *data, t_philo *philo);
t_philo		*initallphilos(t_data *data);
void		*routine(void	*arg);
long long	get_current_time(void);
t_philo		*create_threads(t_philo *philo);
t_philo		*join_threads(t_philo *philo);
void		*galloc(size_t size, int flag);
void		ft_usleep(long long time, t_philo	*philo);
void		print_status(t_philo *philo, int status);
int			monitor(t_philo *philo);
bool		check_death(t_philo	*philo);
int			ft_strcmp(char	*s1, char	*s2);

#endif