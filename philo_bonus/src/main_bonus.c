/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:38:29 by falarm            #+#    #+#             */
/*   Updated: 2022/06/04 17:20:53 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	*check_death(void *data)
{
	t_philo	*philo;

	philo = data;
	while (1)
	{
		if (philo->number_eat)
			if (philo->count_eat == philo->number_eat)
				break ;
		if (get_timestamp() - philo->time_eat > philo->time_to_die)
		{
			philo->death = 1;
			sem_wait(philo->print);
			printf("%lld %d is died\n",
				get_timestamp() - philo->time_start, philo->id);
			break ;
		}
	}
	if (philo->death)
		exit (1);
	else
		exit (0);
}

int	philo_life(t_philo *philo)
{
	if (pthread_create(&philo->check_death, NULL, &check_death, philo))
	{
		printf("Error: pthread create failed!\n");
		return (1);
	}
	if (philo->id % 2 == 0)
		usleep(500);
	while (1)
	{
		if (philo->number_eat)
			if (philo->count_eat == philo->number_eat)
				break ;
		if (philo_eat(philo))
			break ;
	}
	if (pthread_join(philo->check_death, NULL))
	{
		printf("Error: pthread join feiled!\n");
		return (1);
	}
	return (0);
}

int	func(char *str)
{
	printf("%s", str);
	return (1);
}

int	start(t_philo *philo)
{
	int	i;
	int	status;

	i = -1;
	philo->time_start = get_timestamp();
	while (++i < philo->number)
	{
		philo->pid[i] = fork();
		if (philo->pid[i] == -1)
			return (func("Error: fork!\n"));
		if (philo->pid[i] == 0)
		{
			philo->id = i + 1;
			philo->time_eat = philo->time_start;
			if (philo_life(philo))
				return (0);
		}
	}
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			return (killer(philo));
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;

	if (check(argc, argv))
		return (1);
	philo = init_philo(argc, argv);
	if (!philo)
		return (1);
	if (init_sem(philo))
		return (1);
	if (start(philo))
		return (1);
	ft_free(philo);
	return (0);
}
