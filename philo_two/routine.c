/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 15:02:01 by jchotel           #+#    #+#             */
/*   Updated: 2020/05/07 18:42:21 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"
#include <stdio.h>

void		count_meals(t_philo *philo)
{
	philo->n_meals++;
	if (philo->n_meals == philo->data->n_meals && philo->n_meals != 0)
	{
		speak(philo->data->speak, philo, "is done\n");
		while (1)
			;
	}
}

static void	*action(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->data->forks);
		speak(philo->data->speak, philo, "has taken a fork\n");
		sem_wait(philo->data->forks);
		speak(philo->data->speak, philo, "has taken a fork\n");
		sem_wait(philo->eating);
		speak(philo->data->speak, philo, "is eating\n");
		philo->t_death = get_time(philo->data->start) + philo->data->t_die;
		usleep(philo->data->t_eat * 1000);
		sem_post(philo->data->forks);
		sem_post(philo->data->forks);
		count_meals(philo);
		sem_post(philo->eating);
		speak(philo->data->speak, philo, "is sleeping\n");
		usleep(philo->data->t_sleep * 1000);
		speak(philo->data->speak, philo, "is thinking\n");
	}
	return (NULL);
}

int			start_thread(t_philo *philos, t_data *data)
{
	int i;

	i = -1;
	while (++i < data->n_philo)
	{
		if (pthread_create(&philos[i].thr, NULL, action, (void *)&philos[i]))
		{
			free(philos);
			free(data);
			return (1);
		}
		usleep(100);
	}
	return (0);
}

int			end_thread(t_philo *philos, t_data *data)
{
	int i;
	int fed;

	i = -1;
	fed = 0;
	while (++i < data->n_philo)
	{
		if (philos[i].t_death < get_time(data->start) && ((philos[i].n_meals
		!= data->n_meals && data->n_meals != 0) || data->n_meals == 0))
		{
			sem_wait(philos[i].eating);
			sem_wait(data->speak);
			philoprintf(get_time(philos->data->start), philos[i].id, "died\n");
			return (1);
		}
		data->n_meals != 0 && data->n_meals <= philos[i].n_meals ? fed += 1 : 0;
	}
	if (fed == data->n_philo)
	{
		sem_wait(data->speak);
		philoprintf(get_time(philos->data->start), -1, "EVERYONE IS FED\n");
		sem_post(data->speak);
		return (1);
	}
	return (0);
}

void		*loop_end(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (!end_thread(philo, philo[0].data))
		usleep(100);
	return (NULL);
}
