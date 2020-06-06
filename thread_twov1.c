#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 

# include <sys/time.h>

//REF : http://jean-luc.massat.perso.luminy.univ-amu.fr/ens/docs/thread-sem.html


//PRINCIPE : chaque philosophe correspond a un thread
// chaque fourchette ainsi que la parole = un mutex (évite les dédoublements)

typedef struct s_data
{
   int               n_philo;
   int               t_die;
   int               t_eat;
   int               t_sleep;
   int               n_meals;

   sem_t             *speak;
   sem_t             *forks;

   struct timeval    start;
   int               status;
}              t_data;

typedef struct       s_philo
{
   int               id;
   pthread_t         thr;
   long int          t_death;
   int               n_meals;
   t_data            *data;
}                    t_philo;

static int end;


/*************************************************************
** UTILS
**************************************************************/
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

long int get_time(struct timeval start)
{
   struct timeval    time;

   gettimeofday(&time, NULL);
   return ((time.tv_sec - start.tv_sec) * 1000 + 
      (time.tv_usec - start.tv_usec) / 1000);
}

void infos(t_data *data, char *str)
{
   struct timeval    time;
   long int          s;

   s = get_time(data->start);
   printf("%lds %ldms : %s", s / 1000, s % 1000, str);
}






/*************************************************************
** INITS
**************************************************************/
int init_sema(t_data *data)
{
   int i;

   data->speak = sem_open("/speak", O_CREAT , 0666, 1);  //TO BE PROTECTED
   data->forks = sem_open("/forks", O_CREAT , 0666, data->n_philo);
   //what if n_philo = 1 !?
   return (0);
}


t_philo *init_philo(t_data *data)
{
   int i;
   t_philo *philos;

   if (!(philos = (t_philo *)malloc(sizeof(t_philo) * data->n_philo)))
      return (NULL);
   i = 0;
   while (i < data->n_philo)
   {
      philos[i].id = i;
      philos[i].data = data;
      philos[i].t_death = data->t_die * 1000;
      philos[i].n_meals = 0;
      i++;
   }
   return (philos);
}


t_data *init_data(int ac, char **av)
{
   t_data *data;

   if (!(data = (t_data *)malloc(sizeof(t_data))))
      return (NULL);
   if ((data->n_philo = ft_atoi(av[1])) == 0 ||
      (data->t_die = ft_atoi(av[2])) == 0 ||
      (data->t_eat = ft_atoi(av[3])) == 0 ||
      (data->t_sleep = ft_atoi(av[4])) == 0 ||
      (ac == 6 && (data->n_meals = ft_atoi(av[5])) == 0))
      return (NULL);
   data->n_meals = (ac == 5 ? 30 : data->n_meals);
   data->status = 1;
   if(init_sema(data))
      return (NULL);
   return(data);
}
 




/*************************************************************
** FUNCTIONS
**************************************************************/
void speak(sem_t *speak, t_philo *philo, char *str)
{
   sem_wait(speak);
   infos(philo->data, "");
   printf ("Philo %d %s\n", philo->id, str);
   sem_post(speak);
}

void* action (void* ptr) {
   t_philo *philo = (t_philo *) ptr;

   while(philo->data->status) 
   {
      //1 - TAKE FORK
      sem_wait(philo->data->forks);
      speak(philo->data->speak, philo, "has taken a fork");
      //2 - EAT
      sem_wait(philo->data->forks);
      speak(philo->data->speak, philo, "is eating");
      philo->t_death = get_time(philo->data->start) + philo->data->t_eat * 1000 + philo->data->t_die * 1000;
      philo->n_meals += 1;
      sleep(philo->data->t_eat);
      sem_post(philo->data->forks);
      sem_post(philo->data->forks);
      //3 - SLEEP
      speak(philo->data->speak, philo, "is sleeping");
      sleep(philo->data->t_sleep);
      //4 - THINK
      speak(philo->data->speak, philo, "is thinking");
   }
   return NULL;
}

int start_thread(t_philo *philos, t_data *data)
{
   int i;

   i = 0;
   for (i = 0; i < data->n_philo; i++)
   {
      if (pthread_create(&philos[i].thr, NULL, action, &philos[i]))
      {
         printf("Failed to create");
         return (1);
      }
      usleep(100);
   }
   return (0);
}


int is_end(t_philo *philo, t_data *data)
{
   int i;
   int n_fed;

   i = 0;
   n_fed = 0;
   for (i = 0; i < data->n_philo; i++)
   {
      if (philo[i].t_death < get_time(data->start))
      {
         sem_wait(data->speak);
         infos(data, "");
         printf ("Philo %d died at %ld\n", i, philo[i].t_death);
         sem_post(data->speak);
         return (1);
      }
      if (data->n_meals != 0 && data->n_meals <= philo[i].n_meals)
         n_fed += 1;
   }
   if (n_fed == data->n_philo)
   {
      sem_wait(data->speak);
      infos(data, "EVERYONE IS FED\n");
      sem_post(data->speak);
      return (1);
   }
   return (0);
}

static void *loop_end (void *ptr)
{
   t_philo  *philo = (t_philo *)ptr;
   int i;

   i = 0;
   while (!is_end(philo, philo[0].data))
      usleep(100);
   return NULL;
}


int main (int ac, char **av) 
{ 
    t_philo *philos;
    t_data *data;
    pthread_t end;

    int num0 = 0, num1 = 1;

   if ((ac != 5 && ac != 6) || !(data = init_data(ac, av))
      || !(philos = init_philo(data)))
      return (1);
   sem_unlink("/forks");
   sem_unlink("/speak");
   gettimeofday(&data->start, NULL);

   if (start_thread(philos, data))
      return (1);
   pthread_create(&end, NULL, loop_end, philos);
   if (pthread_join(end, NULL))
   {//ATTEND LA FIN DU LOOP
      printf("Failed to join end");
      return (1); 
   }
   return (0);
}

//IL FAUT PENSER A SEM_UNLINK AU DEBUT
//Si on veut attendre la fin d'un thread il faut le join. 
//Ici le programme s'arrête immédiatement après la loop_end