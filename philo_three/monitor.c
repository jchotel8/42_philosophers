/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 15:02:54 by jchotel           #+#    #+#             */
/*   Updated: 2020/05/07 18:39:07 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		check_n_meals(t_data *data)
{
	int		total;

	if (data->n_meals > 0 && !(data->pid_count = fork()))
	{
		total = -1;
		while (total++ < data->n_philo)
			sem_wait(data->over);
		sem_wait(data->speak);
		philoprintf(get_time(data->start), -1, "EVERYONE IS FED\n");
		exit(0);
	}
	return (0);
}

void	*monitor_routine(void *philo_void)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = philo_void;
	while (!i)
	{
		usleep(1000);
		if (get_time(philo->data->start) > philo->t_death &&
		((philo->n_meals != philo->data->n_meals && philo->data->n_meals != 0)
		|| philo->data->n_meals == 0))
		{
			sem_wait(philo->eating);
			sem_wait(philo->data->speak);
			philoprintf(get_time(philo->data->start), philo->id, "died\n");
			i = 1;
		}
	}
	exit(0);
	return (NULL);
}

int		ft_wait(t_philo *philo, int nb)
{
	int status;
	int i;

	while (1)
		if (waitpid(-1, &status, 0) < 0 || WIFEXITED(status))
		{
			i = -1;
			while (++i < nb)
				kill(philo[i].pid, SIGINT);
			return (0);
		}
	return (0);
}
