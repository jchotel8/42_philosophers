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

#include "philo_two.h"

int		init_sema(t_data *data)
{
	char	*eating;
	int		i;

	i = -1;
	sem_unlink("/forks");
	sem_unlink("/speak");
	while (++i < data->n_philo)
	{
		eating = ft_itoa_philo(i);
		sem_unlink(eating);
		free(eating);
	}
	data->speak = sem_open("/speak", O_CREAT, 0666, 1);
	data->forks = sem_open("/forks", O_CREAT, 0666,
	data->n_philo == 1 ? 2 : data->n_philo);
	if (!data->speak || data->speak == SEM_FAILED ||
		!data->forks || data->forks == SEM_FAILED)
	{
		free(data);
		return (1);
	}
	return (0);
}

t_philo	*init_philo(t_data *data)
{
	int		i;
	t_philo	*philos;
	char	*eating;

	if (!(philos = (t_philo *)malloc(sizeof(t_philo) * data->n_philo)))
		return (NULL);
	i = 0;
	while (i < data->n_philo)
	{
		philos[i].id = i;
		philos[i].data = data;
		philos[i].t_death = data->t_die;
		philos[i].n_meals = 0;
		eating = ft_itoa_philo(i);
		philos[i].eating = sem_open(eating, O_CREAT, 0666, 1);
		free(eating);
		if (philos[i].eating == SEM_FAILED)
		{
			free (philos);
			return (NULL);
		}
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
	if (init_sema(data))
		return (NULL);
	return (data);
}
