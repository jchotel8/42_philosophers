/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 17:03:17 by jchotel           #+#    #+#             */
/*   Updated: 2020/05/07 18:44:59 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		init_mutex(t_data *data)
{
	int i;

	if (!(data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
					* data->n_philo)))
		return (1);
	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_unlock(&data->forks[i]);
		i++;
	}
	pthread_mutex_init(&data->speak, NULL);
	pthread_mutex_unlock(&data->speak);
	return (0);
}

t_philo	*init_philo(t_data *data)
{
	int		i;
	t_philo	*philos;

	if (!(philos = (t_philo *)malloc(sizeof(t_philo) * data->n_philo)))
		return (NULL);
	i = 0;
	while (i < data->n_philo)
	{
		philos[i].id = i;
		philos[i].data = data;
		philos[i].fork_l = &data->forks[i];
		philos[i].fork_r = (i == data->n_philo - 1 &&
		data->n_philo != 1 ? &data->forks[0] : &data->forks[i + 1]);
		philos[i].t_death = data->t_die;
		philos[i].n_meals = 0;
		pthread_mutex_init(&philos[i].eating, NULL);
		pthread_mutex_unlock(&philos[i].eating);
		i++;
	}
	return (philos);
}

t_data	*init_data(int ac, char **av)
{
	t_data *data;

	if (!(data = (t_data *)malloc(sizeof(t_data))))
		return (NULL);
	if ((data->n_philo = ft_atoi(av[1])) == 0 ||
	(data->t_die = ft_atoi(av[2])) == 0 ||
	(data->t_eat = ft_atoi(av[3])) == 0 ||
	(data->t_sleep = ft_atoi(av[4])) == 0 ||
	(ac == 6 && (data->n_meals = ft_atoi(av[5])) == 0))
	{
		free(data);
		return (NULL);
	}
	data->n_meals = (ac == 5 ? 0 : data->n_meals);
	if (init_mutex(data))
	{
		free(data->forks);
		free(data);
		return (NULL);
	}
	return (data);
}
