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

#include "philo_three.h"

int		main(int ac, char **av)
{
	t_data		data;

	if (ac != 5 && ac != 6)
		return (ft_error(ERR_MSG));
	if (init_data(&data, ac, av))
		return (1);
	if (init_philos(&data))
		return (1);
	return (0);
}
