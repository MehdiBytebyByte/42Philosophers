/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 00:18:39 by mboughra          #+#    #+#             */
/*   Updated: 2024/12/08 11:14:34 by mboughra         ###   ########.fr       */
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


typedef struct s_garbage
{
	void				*adr;
	struct s_garbage	*next;
}	t_garbage;


typedef struct s_data
{
	int				num;			//number of philo
	int				dietime;		//time to die if philo didn't eat
	int				eatime;			//time to eat
	int				sleeptime;		//time to sleep
	int				meals;			//number of meals each philo should eat if -1 infinite
	long long		start_time;		//start time of the simulation
	bool			dead;			//flag to check if a philo died	
	pthread_mutex_t	*write;			//mutex for write
	pthread_mutex_t	*action;		//mutex for write
	pthread_mutex_t	*check_death;	//one more mutex
}	t_data;
typedef struct s_philo
{
	int				id;				//id of philo
	int				meals_eaten;	//number of meals eaten by philo
	long long		last_meal;		//last time philo ate
	pthread_t		thread;			//thread of philo
	pthread_mutex_t	*left_fork;		//left fork of philo
	pthread_mutex_t	*right_fork;	//right fork of philo
	bool			finished;
	t_data			*data;			//pointer to data (shared by all philos)
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
t_philo		*all_init(t_data *data, t_philo *philo);
t_philo		*initmutix(t_data *data, t_philo *philo);
void		*routine(void	*arg);
long long	get_current_time(void);
t_philo		*create_threads(t_philo *philo);
t_philo		*join_threads(t_philo *philo);
void		*safe_malloc(size_t size, int flag);
void		ft_usleep(long time, t_philo	*philo);
void		print_status(t_philo *philo, char *status);
int			monitor(t_philo *philo);
void		one_philo(t_data	*data);
bool	check_death(t_philo	*philo);



// DETELETE ME
void	print_data(t_data *data);
#endif