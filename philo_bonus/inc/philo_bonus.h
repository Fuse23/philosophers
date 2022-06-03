/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 21:17:04 by falarm            #+#    #+#             */
/*   Updated: 2022/06/03 14:15:41 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>

typedef struct s_philo
{
	int			id;
	int			number;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			number_eat;
	int			count_eat;
	int			death;
	long long	time_start;
	long long	time_eat;
	pid_t		*pid;
	pthread_t	check_death;
	sem_t		*fork;
	sem_t		*print;
}	t_philo;

//main_bonus
int			start(t_philo *philo);
int			philo_life(t_philo *philo);
void		*check_death(void *data);
int			func(char *str);

//utils_bonus
long long	ft_atoi(const char *str);
long long	get_timestamp(void);
void		ft_usleep(long long time);
void		ft_free(t_philo *philo);
int			killer(t_philo *philo);

//init_bonus
int			check(int ac, char **av);
t_philo		*init_philo(int ac, char **av);
int			init_sem(t_philo *philo);

//philo_bonus
void		philo_print(t_philo *philo, char *str);
int			philo_eat(t_philo *philo);

#endif
