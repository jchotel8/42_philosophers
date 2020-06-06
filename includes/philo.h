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

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>

# include "../libs/libft/libft.h"
# include "../libs/ft_printf/includes/printf.h"

#define	LIFE_POINT	10

#define	DEAD		0
#define	THINKING	1
#define	SLEEPING	2
#define EATING		3

#define SUCCESS		0
#define FAIL		1

typedef struct		s_philo
{
	int				id;
	int				state;
	pthread_mutex_t *fork_l;
	pthread_mutex_t *fork_r;
	pthread_t 		*thr;
}					t_philo;

typedef struct 		s_data
{
	int 			n_philo;
	int 			t_eat;
	int				t_think;
	int 			t_sleep;
	int 			t;
	struct timeval 	start;
	pthread_mutex_t *forks;
	t_philo 		*philo;
}					t_data;



void *live(void *str);
//ACTION
void 		infos(t_data *data, char *str);
void		*action(void *i);

//INIT
int 		init_data(int ac, char **av, t_data *data);

//UTILS
int 		ft_error(char *type_error);
int			free_error(char *type_error, t_data *data, pthread_mutex_t *forks, t_philo *philo);
void		debug(t_philo *philo);
void		debug_list(t_philo *philo, int taille);

#endif
