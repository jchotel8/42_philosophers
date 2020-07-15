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

#include "philo_three.h"

t_philo			*set_philos(t_data *data)
{
	t_philo	*philo;
	char	*eating;
	int		i;

	if (!(philo = (t_philo *)malloc(sizeof(t_philo) * data->n_philo)))
		return (NULL);
	i = -1;
	while (++i < data->n_philo)
	{
		philo[i].id = i;
		philo[i].data = data;
		philo[i].t_death = data->t_die;
		philo[i].n_meals = 0;
		eating = ft_itoa_philo(i);
		philo[i].eating = sem_open(eating, O_CREAT, 0666, 1);
		free(eating);
		if (!philo[i].eating || philo[i].eating == SEM_FAILED)
		{
			free(philo);
			return (NULL);
		}
	}
	gettimeofday(&data->start, NULL);
	return (philo);
}

int			init_philos(t_data *data)
{
	t_philo		*philo;
	int			i;

	if (!(philo = set_philos(data)))
		return (ft_error("Error: init_philos\n"));
	i = -1;
	while (++i < data->n_philo)
	{
		if ((philo[i].pid = fork()) == 0)
		{
			if (pthread_create(&philo[i].monitor_thr, NULL,
			&monitor_routine, &philo[i]) != 0)
			{
				free(philo);
				return (ft_error("Error: pthread failed!\n"));
			}
			action(&philo[i]);
			exit(0);
		}
		usleep(10);
	}
	check_n_meals(data);
	ft_wait(philo, data->n_philo);
	free(philo);
	return (0);
}

int			init_sema(t_data *data)
{
	char	*eating;
	int		i;

	i = -1;
	sem_unlink("/forks");
	sem_unlink("/speak");
	sem_unlink("/over");
	while (++i < data->n_philo)
	{
		eating = ft_itoa_philo(i);
		sem_unlink(eating);
		free(eating);
	}
	data->forks = sem_open("/forks", O_CREAT, 0666,
	data->n_philo == 1 ? 2 : data->n_philo);
	data->speak = sem_open("/speak", O_CREAT, 0666, 1);
	data->over = sem_open("/over", O_CREAT, 0666, 1);
	if (!data->forks || data->forks == SEM_FAILED
	|| !data->speak || data->speak == SEM_FAILED
	|| !data->over || data->over == SEM_FAILED)
		return (1);
	return (0);
}

int			init_data(t_data *data, int ac, char **av)
{
	if ((data->n_philo = ft_atoi(av[1])) == 0 ||
	(data->t_die = ft_atoi(av[2])) == 0 ||
	(data->t_eat = ft_atoi(av[3])) == 0 ||
	(data->t_sleep = ft_atoi(av[4])) == 0 ||
	(ac == 6 && (data->n_meals = ft_atoi(av[5])) == 0))
		return (ft_error("Error: bad arguments\n"));
	data->n_meals = (ac == 5 ? 0 : data->n_meals);
	if (init_sema(data))
		return (ft_error("Error: semaphore not created\n"));
	return (0);
}
