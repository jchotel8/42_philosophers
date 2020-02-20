/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 00:37:27 by jchotel           #+#    #+#             */
/*   Updated: 2020/01/24 07:10:11 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	debug(t_philo *philo)
{
	printf("---------------------\n");
	printf("id :\t%d\n", philo->id);
	printf("life :\t%i\n", philo->life);
	printf("state :\t%i\n", philo->state);
	if (philo->prev)
		printf("prev :\t%d\n", philo->prev->id);
	if (philo->next)
		printf("next :\t%d\n", philo->next->id);
}

void debug_list(t_philo *philo, int taille)
{
	debug(philo);
	while (taille > 0)
	{
		philo = philo->next;
		debug(philo);
		taille--;
	}
}

t_philo	*init_list(int nb_philo, t_philo *prev)
{
	t_philo *philo;

	if (nb_philo <= 0)
		return (0);
	if ((philo = (t_philo *)malloc(sizeof(t_philo))))
	{
		philo->id = --nb_philo + 1;
		philo->life = LIFE_POINT;
		philo->prev = prev;
		philo->next = init_list(nb_philo, philo);
	}
	return (philo);
}

void	init_state(t_philo *philo, int taille)
{
	while (taille > 0)
	{
		if (nb_fork(philo) == 2)
			philo->state = EATING;
		else if (nb_fork(philo) == 1)
			philo->state = THINKING;
		else
			philo->state = SLEEPING;
		philo = philo->next;
		taille--;
	}
}

t_philo *init_table(int nb_philo)
{
	t_philo *last;
	t_philo *philo;

	philo = init_list(nb_philo, NULL);
	last = philo;
	while (last && last->next)
		last = last->next;
	if(last)
	{
		last->next = philo;
		philo->prev = last;
	}
	init_state(philo, nb_philo);
	return (philo);
}