/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 14:24:45 by falarm            #+#    #+#             */
/*   Updated: 2022/05/22 20:54:08 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

typedef struct s_philo
{
	int			id;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			count_eat;
	int			left_fork;
	int			right_fork;
	long long	time_start;
	long long	last_eat;
	t_table		*args;
}	t_philo;

typedef struct s_table
{
	int				count_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				count_of_eat;
	int				flag_of_death;
	long long		time_start;
	pthread_t		*thread;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	t_philo			*philo;
}	t_table;

//utils
long long	ft_atoi(const char *str);
long long	get_timestamp(void);
int			ft_free(t_table *table);
void		ft_destroy_mutex(t_table *table);
void		ft_usleep(long long time);

//init
t_table		*init_table(int ac, char **av);
int			check(int ac, char **av);
int			malloc_philo(t_table *table);
int			init_philo(t_table *table, int ac, char **av);

//philo
void		philo_print(t_table	*table, t_philo *philo, char *str);
int			eating(t_table *table, t_philo *philo);
void		sleeping(t_table *table, t_philo *philo);
void		thinking(t_table *table, t_philo *philo);

//main
void		start(t_table *table);
void		philo_life(void *data);
void		death(void *data);

#endif
