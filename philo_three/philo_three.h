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

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

# define ERR_MSG "./philo n_philo t_die t_eat t_sleep [n_of_meals]\n"
# define RED "\033[0;0m\x1b[38;2;232;72;119m"
# define WHI "\x1b[38;2;255;235;202m"
# define YEL "\x1b[38;2;232;212;98m"
# define TIME 15

typedef struct			s_data
{
	int					n_philo;
	unsigned long		t_die;
	unsigned long		t_eat;
	unsigned long		t_sleep;
	int					n_meals;

	struct timeval		start;

	sem_t				*forks;
	sem_t				*speak;
	sem_t				*over;
	pid_t				pid_count;
}						t_data;

typedef struct			s_philo
{
	int					id;
	pid_t				pid;
	pthread_t			monitor_thr;
	sem_t				*eating;
	long int			t_death;
	int					n_meals;
	t_data				*data;
}						t_philo;
/*
**UTILS
*/
long int				get_time(struct timeval start);
void					speak(sem_t *speak, t_philo *philo, char *str);
/*
**INIT
*/
int						init_data(t_data *data, int ac, char **av);
int						init_sema(t_data *data);
int						init_philos(t_data *data);
/*
**ROUTINE
*/
void					action(t_philo *philo);
/*
**MONITOR
*/
void					*monitor_routine(void *philo_void);
int						check_n_meals(t_data *data);
int						ft_wait(t_philo *philo, int nb);

/*
**LIB
*/
int						ft_error(char *s);
void					ft_putstr(char *s);
void					ft_putnbr(unsigned long n);
int						ft_atoi(const char *str);
int						ft_putchar(char c);
char					*ft_itoa_philo(int i);
int						philoprintf(long int time, int id, char *str);
#endif
