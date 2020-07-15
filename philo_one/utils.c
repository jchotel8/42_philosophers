/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 16:24:11 by jchotel           #+#    #+#             */
/*   Updated: 2020/05/07 18:18:39 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

long int	get_timestamp(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_usec / 1000 + tv.tv_sec * 1000);
}

long int	get_time(struct timeval start)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec - start.tv_sec) * 1000 +
			(time.tv_usec - start.tv_usec) / 1000);
}

void		speak(pthread_mutex_t *speak, t_philo *philo, char *str)
{
	pthread_mutex_lock(speak);
	philoprintf(get_time(philo->data->start), philo->id, str);
	pthread_mutex_unlock(speak);
}
