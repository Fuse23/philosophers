/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 21:15:33 by falarm            #+#    #+#             */
/*   Updated: 2022/06/02 21:45:51 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	philo_print(t_philo *philo, char *str)
{
	sem_wait(philo->print);
	printf("%lld %d %s\n",
		get_timestamp() - philo->time_start, philo->id, str);
	sem_post(philo->print);
}

int	philo_eat(t_philo *philo)
{
	sem_wait(philo->fork);
	philo_print(philo, "has taken a fork");
	if (philo->number == 1)
	{
		sem_post(philo->fork);
		return (1);
	}
	sem_wait(philo->fork);
	philo_print(philo, "has taken a fork");
	philo_print(philo, "is eating");
	philo->time_eat = get_timestamp();
	ft_usleep(philo->time_to_eat);
	sem_post(philo->fork);
	sem_post(philo->fork);
	philo->count_eat++;
	philo_print(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
	philo_print(philo, "is thinking");
	return (0);
}
