/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 16:24:20 by jchotel           #+#    #+#             */
/*   Updated: 2020/05/07 18:36:34 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

# define ERR_MSG "./philo n_philo t_die t_eat t_sleep [n_of_meals]\n"
# define RED "\033[0;0m\x1b[38;2;232;72;119m"
# define WHI "\x1b[38;2;255;235;202m"
# define YEL "\x1b[38;2;232;212;98m"
# define TIME 10

typedef struct		s_data
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_meals;
	pthread_mutex_t	speak;
	pthread_mutex_t	*forks;
	struct timeval	start;
}					t_data;

typedef struct		s_philo
{
	int				id;
	pthread_t		thr;
	pthread_mutex_t	eating;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*fork_l;
	long int		t_death;
	int				n_meals;
	t_data			*data;
}					t_philo;
/*
** UTILS
*/
long int			get_time(struct timeval start);
void				speak(pthread_mutex_t *speak, t_philo *philo, char *str);
/*
** INIT
*/
t_data				*init_data(int ac, char **av);
int					init_sema(t_data *data);
t_philo				*init_philo(t_data *data);
/*
** ROUTINE
*/
int					end_thread(t_philo *philos, t_data *data);
int					start_thread(t_philo *philos, t_data *data);

/*
** LIB
*/
int					ft_error(char *s);
void				ft_putstr(char *s);
void				ft_putnbr(unsigned long n);
int					ft_atoi(const char *str);
int					ft_putchar(char c);
int					philoprintf(long int time, int id, char *str);

#endif
