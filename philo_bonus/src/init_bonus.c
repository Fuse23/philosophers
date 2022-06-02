/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:55:18 by falarm            #+#    #+#             */
/*   Updated: 2022/06/02 21:38:07 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	check(int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		printf("Error: Wrong number argments!");
		return (1);
	}
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[2]) <= 0
		|| ft_atoi(av[3]) <= 0 || ft_atoi(av[4]) <= 0
		|| (ac == 6 && ft_atoi(av[5]) <= 0))
	{
		printf("Error: Wrong arguments!");
		return (1);
	}
	return (0);
}

t_philo	*init_philo(int ac, char **av)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->number = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	philo->number_eat = 0;
	if (ac == 6)
		philo->number_eat = ft_atoi(av[5]);
	philo->count_eat = 0;
	philo->death = 0;
	philo->time_start = 0;
	philo->time_eat = 0;
	return (philo);
}

int	init_sem(t_philo *philo)
{
	sem_unlink("print");
	sem_unlink("fork");
	philo->print = sem_open("print", O_CREAT, 0644, 1);
	if (philo->print == SEM_FAILED)
	{
		printf("Error: sem failed!\n");
		free(philo);
		return (1);
	}
	philo->fork = sem_open("fork", O_CREAT, 0644, philo->number);
	if (philo->fork == SEM_FAILED)
	{
		printf("Error: sem failed!\n");
		free(philo);
		return (1);
	}
	philo->pid = malloc(sizeof(pid_t) * philo->number);
	if (!philo->pid)
	{
		sem_close(philo->print);
		sem_close(philo->fork);
		free(philo);
		return (1);
	}
	return (0);
}
