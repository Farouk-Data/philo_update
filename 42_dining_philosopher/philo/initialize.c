/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 02:37:39 by fech-cha          #+#    #+#             */
/*   Updated: 2022/06/17 20:56:31 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data **data, int ac, char **av)
{
	*data = (t_data *)malloc(sizeof(t_data));
	if (!*data)
		return (0);
	(*data)->n_philos = ft_atoi(av[1]);
	(*data)->time_die = ft_atoi(av[2]);
	(*data)->time_eat = ft_atoi(av[3]);
	(*data)->time_sleep = ft_atoi(av[4]);
	(*data)->nom = -1;
	if (ac == 6)
		(*data)->nom = ft_atoi(av[5]);
	return (0);
}

int	monitor_inits(t_monitor **monitor_obj, int nuphilo)
{
	int			i;
	t_monitor	*monitor;

	monitor = (t_monitor *)malloc(sizeof(t_monitor));
	if (!monitor)
		return (0);
	monitor->start = 0;
	monitor->status = true;
	monitor->mutex_forks = malloc(sizeof(pthread_mutex_t) * nuphilo);
	if (!monitor->mutex_forks)
		return (0);
	i = -1;
	while (++i < nuphilo)
		if (pthread_mutex_init(monitor->mutex_forks + i, NULL))
			return (-1);
	if (pthread_mutex_init(&monitor->mutex_print, NULL))
		return (-1);
	*monitor_obj = monitor;
	return (0);
}

int	init_philos(t_philo **philo, t_cont *monitor, \
	pthread_mutex_t *mutex_forks, int nphilo)
{	
	int	i;

	*philo = (t_philo *)malloc(sizeof(t_philo) * nphilo);
	if (!*philo)
		return (0);
	i = -1;
	while (++i < nphilo)
	{
		(*philo + i)->philosopher = i + 1;
		(*philo + i)->nbr_of_meals = 0;
		(*philo + i)->last_eat = 0;
		(*philo + i)->cont = monitor;
		(*philo + i)->l_fork = mutex_forks + i;
		(*philo + i)->r_fork = mutex_forks + ((i + 1) % nphilo);
	}
	return (0);
}

int	init(t_cont **cont_obj, int ac, char **av)
{
	t_cont	*cnt;

	cnt = (t_cont *)malloc(sizeof(t_cont));
	if (!cnt)
		return (0);
	if (init_data(&cnt->data, ac, av) == -1)
		return (-1);
	if (monitor_inits(&cnt->moni, cnt->data->n_philos) == -1)
		return (-1);
	if (init_philos(&cnt->philo, cnt, \
		cnt->moni->mutex_forks, cnt->data->n_philos) == -1)
		return (-1);
	*cont_obj = cnt;
	return (0);
}
