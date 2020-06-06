/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
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
	//printf("life :\t%i\n", philo->life);
	printf("state :\t%s\n", philo->state == 2 ? "EATING": philo->state == 1 ? "THINKING" : "SLEEPING");
	// if (philo->prev)
	// 	printf("prev :\t%d\n", philo->prev->id);
	// if (philo->next)
	// 	printf("next :\t%d\n", philo->next->id);
}

// void debug_list(t_philo *philo, int taille)
// {
// 	debug(philo);
// 	while (taille > 0)
// 	{
// 		philo = philo->next;
// 		debug(philo);
// 		taille--;
// 	}
// }

// int ft_strlen(char *str)
// {
// 	int i;

// 	i = 0;
// 	while 
// }

int ft_error(char *type_error)
{
	ft_printf("ERROR : %s\n", type_error);
	return (1);
}

int free_error(char *type_error, t_data *data, pthread_mutex_t *forks, t_philo *philo)
{
	if (forks)
		free(forks);
	if (philo)
		free(philo);
	if (data)
		free(data);
	if (type_error)
	{
		ft_error(type_error);
		return (1);
	}
	return (0);
}