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

int main(int ac, char **av)
{
	t_philo *philo;
	if (ac > 0 && av[1])
		philo = init_table(6);
	debug_list(philo, 5);
	//action(philo, 5);
}
