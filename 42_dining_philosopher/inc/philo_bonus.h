/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 05:14:42 by fech-cha          #+#    #+#             */
/*   Updated: 2022/06/16 02:54:48 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_data
{
	int				nop;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				nom;
}	t_data;

typedef struct s_philo
{
	int				philo_number;
	pthread_t		philo_thread;
	int				eat_counter;
	size_t			last_meal_time;
	struct s_contain	*contain;
	pid_t			*pid;
	bool			isdied;
}	t_philo;

typedef struct s_monitor
{
	size_t			start_time;
	bool			status;
	pthread_t		thread_monitor;
	sem_t			sem_printf;
	sem_t			*sem_forks;
	sem_t			*sem_write;
}	t_monitor;

typedef struct s_contain
{
	t_data	*data;
	t_philo	*philo;
	t_monitor	*monitor;
}	t_contain;

int			ft_strlen(const char *s);
int			ft_isnumber(char *str);
int			ft_strcmp(char *s1, char *s2);
long int	ft_atoi(const char *str);
long long	current_timestamp(void);
int			init_contain_bonus(t_philo **philo, int ac, char **av);
int			philo_start_bonus(t_philo *philo);
void		philo_end(t_philo **philo);
#endif