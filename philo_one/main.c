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

#include "philo_one.h"

int		main(int ac, char **av)
{
	t_philo	*philos;
	t_data	*data;

	if ((ac != 5 && ac != 6) || !(data = init_data(ac, av)))
		return (ft_error(ERR_MSG));
	if (!(philos = init_philo(data)))
	{
		free(data);
		return (ft_error("Error in init_philo()\n"));
	}
	gettimeofday(&data->start, NULL);
	if (start_thread(philos, data))
		return (ft_error("Error starting threads\n"));
	while (1)
	{
		usleep(100);
		if (end_thread(philos, data))
			return (0);
	}
	return (0);
}
