/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 00:37:27 by jchotel           #+#    #+#             */
/*   Updated: 2020/01/24 07:10:11 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int init_fork(t_data *data)
{
	int forks;
	int i;

	i = 0;
	forks = (data->n_philo == 1 ? 2 : data->n_philo);
	if ((data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * forks)) == NULL)
		return (FAIL);
	while (i < forks)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_unlock(&data->forks[i]);
		i++;
	}
	return (SUCCESS);
}

int init_philo(t_data *data)
{
	int i;

	i = 0;
	char *str = "bonjour";
	if ((data->philo = (t_philo *)malloc(sizeof(t_philo) * data->n_philo)) == NULL)
		return (FAIL);
	while (i < data->n_philo)
	{
		data->philo[i].id = i;
		data->philo[i].state = THINKING;
		data->philo[i].fork_l = &data->forks[i];
		data->philo[i].fork_r = (i == data->n_philo - 1 && data->n_philo != 1 ? &data->forks[0] : &data->forks[i + 1]);
		//pthread_create(data->philo[i].thr, NULL, action, &str);
		//pthread_mutex_init(&data->philo[i].thread, NULL);
		//pthread_mutex_unlock(&data->philo[i].thread);
		i++;
	}
	return (SUCCESS);
}

int init_data(int ac, char **av, t_data *data)
{
	if ((data->n_philo = ft_atoi(av[1])) == 0 ||
		(data->t_eat = ft_atoi(av[2])) == 0 ||
		(data->t_think = ft_atoi(av[3])) == 0 ||
		(data->t_sleep = ft_atoi(av[4])) == 0 ||
		(ac == 6 && (data->t = ft_atoi(av[5])) == 0))
		return (free_error("null arguments", data, NULL, NULL));
	if (init_fork(data))
		return (free_error("failed to init forks", data, NULL, NULL));
	if (init_philo(data))
		return (free_error("failed to init philos", data, data->forks, NULL));
	gettimeofday(&data->start, NULL);
	return (SUCCESS);
}