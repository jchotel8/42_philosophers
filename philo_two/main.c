/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 16:24:03 by jchotel           #+#    #+#             */
/*   Updated: 2020/05/07 17:48:36 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int	main(int ac, char **av)
{
	t_philo		*philos;
	t_data		*data;
	pthread_t	end;

	if ((ac != 5 && ac != 6) || !(data = init_data(ac, av))
		|| !(philos = init_philo(data)))
		return (ft_error(ERR_MSG));
	gettimeofday(&data->start, NULL);
	if (start_thread(philos, data))
		return (1);
	pthread_create(&end, NULL, loop_end, philos);
	if (pthread_join(end, NULL))
		return (ft_error("Failed to join end"));
	return (0);
}
