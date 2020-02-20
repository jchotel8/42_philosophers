/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 21:30:14 by jchotel           #+#    #+#             */
/*   Updated: 2020/01/24 06:22:40 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H
# include <stdarg.h>
# include <stdio.h>
# include "libft.h"

#define	LIFE_POINT	10
#define	EAT_TIME	1
#define	SLEEP_TIME	1
#define	THINK_TIME	1

#define	DEAD		0
#define	THINKING	1
#define	SLEEPING	2
#define EATING		3


typedef struct		s_philo
{
	int				id;
	int				life;
	int				state;
	struct s_philo	*next;
	struct s_philo	*prev;
}					t_philo;

//ACTION
//void	eat(t_philo *philo);
//void	sleep();
//void	think();
void		action(t_philo *philo, int taille);
int			nb_fork(t_philo *philo);
//INIT
t_philo		*init_table(int nb_philo);

void		debug(t_philo *philo);
void		debug_list(t_philo *philo, int taille);

#endif
