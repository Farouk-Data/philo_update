/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 02:37:42 by fech-cha          #+#    #+#             */
/*   Updated: 2022/06/17 22:09:31 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *args)
{
	t_philo	*philo;
	int		flag;
	int		i;

	philo = (t_philo *)args;
	while (philo->cont->moni->status)
	{
		i = -1;
		flag = 0;
		while (++i < philo->cont->data->n_philos)
		{
			if (get_time() - (philo + i)->last_eat
				> philo->cont->data->time_die)
			{
				print_action(philo + i, "is died");
				philo->cont->moni->status = false;
			}
			if (philo->cont->data->nom != -1 && (philo + i)->nbr_of_meals
				>= philo->cont->data->nom)
				flag++;
		}
		if (flag == philo->cont->data->n_philos)
			philo->cont->moni->status = false;
	}
	return (NULL);
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	philo->cont->moni->start = get_time();
	while (philo->cont->moni->status)
	{
		print_action (philo, "is thinking");
		pthread_mutex_lock (philo->l_fork);
		print_action (philo, "took the left fork");
		pthread_mutex_lock (philo->r_fork);
		print_action (philo, "took the right fork");
		print_action (philo, "is eating");
		retard_proc (philo->cont->data->time_eat, philo);
		philo->last_eat = get_time();
		pthread_mutex_unlock (philo->l_fork);
		pthread_mutex_unlock (philo->r_fork);
		if (philo->cont->moni->status)
			philo->nbr_of_meals++;
		print_action (philo, "is sleeping");
		retard_proc (philo->cont->data->time_sleep, philo);
	}
	return (NULL);
}

int	execution(t_philo	*philo)
{
	int	i;

	i = -1;
	philo->cont->moni->start = get_time();
	while (++i < philo->cont->data->n_philos)
	{
		(philo + i)->last_eat = get_time();
		if (pthread_create (&(philo + i) \
			->philo_thread, NULL, routine, philo + i))
			return (printf ("error occured while creating thread"), 0);
		pthread_detach((philo + i)->philo_thread);
		usleep(50);
	}
	if (pthread_create(&philo->cont->moni->sup_thread, NULL, monitor, philo))
		return (printf("error occured while creating thread"), 0);
	if (pthread_join(philo->cont->moni->sup_thread, NULL))
		return (printf ("error occured while joining"), 0);
	i = -1;
	while (++i < philo->cont->data->n_philos)
		pthread_mutex_destroy(&philo->cont->moni->mutex_forks[i]);
	pthread_mutex_destroy(&philo->cont->moni->mutex_print);
	return (0);
}
