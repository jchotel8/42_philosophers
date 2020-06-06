/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 01:09:43 by jchotel           #+#    #+#             */
/*   Updated: 2020/01/24 06:22:29 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

int	ft_init_start(t_data *data)
{
	gettimeofday(&data->start, NULL);
	return (0);
}

int main(int ac, char **av)
{
	t_data data;
	int i;

	if (ac != 5 && ac != 6)
		return (ft_error("missing arguments"));
	if (init_data(ac, av, &data))
		return (FAIL);
	i = 0;
	while (i < data.n_philo)
	{
		pthread_create(data.philo[i].thr, NULL, action, NULL);
		i++;
	}
	i = 0;
	while (i < data.n_philo)
	{
		pthread_join(*data.philo[i].thr, NULL);
		i++;
	}
	//infos(&data, "philosophers are ready");
	
}



// THREAD ET MUTEX : https://franckh.developpez.com/tutoriels/posix/pthreads/