/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 14:23:21 by falarm            #+#    #+#             */
/*   Updated: 2022/05/22 20:50:18 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	death(void *data)
{
	t_table	*table;
	int		i;

	i = -1;
	table = data;
	while (++i < table->count_philo)
	{
		if (table->count_of_eat)
			if (table->philo[i].count_eat == table->count_of_eat)
				return (NULL);
		if (get_timestamp() - table->philo[i].last_eat > table->time_to_die)
		{
			table->flag_of_death = 1;
			pthread_mutex_lock(&table->print);
			printf("%lld %d is died\n",
					get_timestamp() - table->philo[i].time_start, table->philo[i].id);
			return (NULL);
		}
	}
}

void	philo_life(void *data)
{
	
}

void	start(t_table *table)
{
	int			i;
	pthread_t	check;

	i = -1;
	table->time_start = get_timestamp();
	while (++i < table->count_philo)
	{
		table->philo[i].time_start = table->time_start;
		table->philo[i].last_eat = table->time_start;
	}
	i = -1;
	while (++i < table->count_philo)
		pthread_create(table->thread[i], NULL, &philo_life, &table->philo[i]);
	pthread_create(&check, NULL, death, table);
	pthread_mutex_unlock(&table->print);
	pthread_join(check, NULL);
	i = -1;
	while (++i < table->count_philo)
		pthread_join(table->thread[i], NULL);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	if (check(argc, argv))
		return (1);
	table = init_table(argc, argv);
	if (!table)
		return (1);
	if (malloc_philo(table))
		return (ft_free(table));
	if (init_philo(table, argc, argv))
		return(ft_free(table));
	strat(table);
	ft_destroy_mutex(table);
	ft_free(table);
	return (0);
}