#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
 
#if defined (Win32)
#  include <windows.h>
#  define psleep(sec) Sleep ((sec) * 1000)
#elif defined (Linux)
#  include <unistd.h>
#  define psleep(sec) sleep ((sec))
#endif
 
#define INITIAL_STOCK   20
#define NB_PHILO      3

//PRINCIPE : chaque philosophe correspond a un thread
// chaque fourchette ainsi que la parole a un mutex (évite les dédoublements)

typedef struct s_data
{
   int               n_philo;
   int               t_die;
   int               t_eat;
   int               t_sleep;
   int               n_meals;

   pthread_mutex_t   speak;
   pthread_mutex_t   forks;

   int               alive;
   struct timeval    start;
}              t_data;

typedef struct       s_philo
{
   int               id;
   pthread_t         thr;
   int               fork_r;
   int               fork_l;
   //t_death
   //n_meals
   t_data            *data;
}                    t_philo;













int   ft_atoi(const char *str)
{
   unsigned int   res;
   size_t         i;
   int            sign;

   res = 0;
   i = 0;
   sign = 1;
   while ((str[i] >= 8 && str[i] <= 13) || str[i] == ' ')
      i++;
   if (str[i] == '+' || str[i] == '-')
      if (str[i++] == '-')
         sign = -sign;
   while (str[i] >= '0' && str[i] <= '9')
      res = res * 10 + str[i++] - '0';
   return (res * sign);
}

void infos(t_data *data, char *str)
{
   struct timeval    time;
   long int          s;
   int               ms;

   gettimeofday(&time, NULL);
   s = time.tv_sec - data->start.tv_sec;
   ms = (time.tv_usec - data->start.tv_usec) / 1000;
   s = ms < 0 ? s - 1 : s;
   ms = ms < 0 ? 1000 + ms: ms;
   printf("%lds %ims : %s", s, ms, str);
}







// void init_mutex(t_data *data)
// {
//    int i;

//    pthread_mutex_init(&data->speak, NULL);
//    pthread_mutex_unlock(&data->speak);
//    i = 0;
//    while (i < NB_PHILO)
//    {
//       pthread_mutex_init(&data->forks[i], NULL);
//       pthread_mutex_unlock(&data->forks[i]);
//       i++;
//    }
// }


int init_philo(t_philo *philos, t_data *data)
{
   int i;

   // if ((philos = (t_philo *)malloc(sizeof(t_philo) * NB_PHILO)) == NULL)
   //    return (1);
   i = 0;
   while (i < NB_PHILO)
   {
      philos[i].id = i;
      philos[i].data = data;
      philos[i].fork_l = i;
      philos[i].fork_r = (i == NB_PHILO - 1 && NB_PHILO != 1 ? 0 : i + 1);
      i++;
   }
   return (0);
}


int init_data(int ac, char **av, t_philo *philos)
{
   int i;
   t_data *data;

   if ((data = (t_data *)malloc(sizeof(t_data))) == NULL)
      return (1);
   if ((data->n_philo = ft_atoi(av[1])) == 0 ||
      (data->t_die = ft_atoi(av[2])) == 0 ||
      (data->t_eat = ft_atoi(av[3])) == 0 ||
      (data->t_sleep = ft_atoi(av[4])) == 0 ||
      (ac == 6 && (data->n_meals = ft_atoi(av[5])) == 0))
      return (1);
   data->alive = 1;
   pthread_mutex_init(&data->speak, NULL);
   pthread_mutex_unlock(&data->speak);
   if (init_philo(philos, data))
      return (1);
   gettimeofday(&data->start, NULL);
   return(0);
}
 
/* Fonction pour les threads des clients. */
static void *action (void * arg)
{
   t_philo  *philo = (t_philo *) arg;
   while (philo->data->alive)
   {
      //1 - TAKE FORKS
      //2 - EAT - wait t_eat - set t_death = time + data->t_die
      //3 - SLEEP - wait t_sleep
      //4 - THINK - wait for the forks

      sleep (4);

      pthread_mutex_lock (&philo->data->speak);
      usleep(500000);  //0.5 sec //it should be 
      infos(philo->data, "");
      printf ("Philo %d prend les fourchettes %d et %d\n", philo->id, philo->fork_l, philo->fork_r);
      pthread_mutex_unlock (&philo->data->speak);
   }
 
   return NULL;
}
 
int main (int ac, char **av)
{
   int      i;
   int      nb;
   t_philo  philo[NB_PHILO];
 
   if ((ac != 5 && ac != 6) || init_data(ac, av, philo))
      return (1);
   i = 0;
   for (i = 0; i < NB_PHILO; i++)
   {
      // write(1, "12345\n", 6);
      if (pthread_create(&philo[i].thr, NULL, action, (void *)&philo[i]))
         return 1;
   }
 
 
   i = 0;
   for (i = 0; i < NB_PHILO; i++)
      pthread_join(philo[i].thr, NULL);
   return 0;
}
