/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 21:46:13 by jchotel           #+#    #+#             */
/*   Updated: 2020/01/24 07:17:01 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int nb_fork(t_philo *philo)
{
	if (philo->prev->state != EATING && philo->next->state != EATING)
		return (2);
	else if (philo->prev->state != EATING || philo->next->state != EATING)
		return (1);
	return (0);
}

void	eat(t_philo *philo)
{
	int time;

	time = 0;
	while (philo->state == EATING && time++ < EAT_TIME && philo->life < LIFE_POINT)
	{
		//attendre 1seconde
		philo->life++;
	}
	printf("- %d is sleeping\n", philo->id);
	philo->state = SLEEPING;
		//sleep(philo);
}
//
//void	sleep(t_philo *philo)
//{
//	int	time;
//
//	time = 0;
//	philo->state = SLEEPING;
//	while (philo->state != DEAD && time++ < SLEEP_TIME)
//	{
//		//attendre 1s;
//		philo->life--;
//		if (philo->life <= 0)
//			philo->state = DEAD;
//	}
//	if (philo->state != DEAD)
//		think(philo);
//}
//
//void	think(t_philo *philo)
//{
//	int time;
//
//	time = 0;
//	philo->state = THINKING;
//	while (time++ < THINK_TIME)
//	{
//		//attendre 1s
//		philo->life--;
//		if (philo->life <= 0)
//			philo->state = DEAD;
//	}
//	if (philo->state != DEAD)
//		eat(philo);
//}
//
//void	start_cycle(t_philo *philo)
//{
//	if (philo->next->state == EAT || philo->prev->state == EAT)
//	else if ()
//}

void action(t_philo *philo, int taille)
{
	eat(philo);
	while (taille > 0)
	{
		philo = philo->next;
		eat(philo);
		taille--;
	}
}