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

#include "philo_three.h"

void	count_meals(t_philo *philo)
{
	philo->n_meals++;
	if (philo->n_meals == philo->data->n_meals && philo->n_meals != 0)
	{
		speak(philo->data->speak, philo, "is done\n");
		sem_post(philo->data->over);
		while (1)
			;
	}
}

void	action(t_philo *philo)
{
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
}
