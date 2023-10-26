/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 02:38:39 by fech-cha          #+#    #+#             */
/*   Updated: 2022/06/16 02:57:12 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	current_timestamp(void)
{
	struct timeval	te;
	long long		milliseconds;

	gettimeofday(&te, NULL);
	milliseconds = (te.tv_sec * 1000) + (te.tv_usec / 1000);
	return (milliseconds);
}

int	init_data(t_data **data, int ac, char **av)
{
	t_data	*tmp;

	tmp = (t_data *)malloc(sizeof(t_data));
	if (!tmp)
		return (printf("Allocation Failed\n"), -1);
	tmp->nop = ft_atoi(av[1]);
	tmp->time_to_die = ft_atoi(av[2]);
	tmp->time_to_eat = ft_atoi(av[3]);
	tmp->time_to_sleep = ft_atoi(av[4]);
	tmp->nom = -1;
	if (ac == 6)
		tmp->nom = ft_atoi(av[5]);
	*data = tmp;
	return (0);
}

int	init_monitor(t_monitor **monitor, int nop)
{
	t_monitor	*tmp;

	tmp = (t_monitor *)malloc(sizeof(t_monitor));
	if (!tmp)
		return (printf("Allocation Failed\n"), -1);
	tmp->start_time = 0;
	tmp->status = true;
	sem_unlink("/sem_write");
	sem_unlink("/sem_forks");
	tmp->sem_write = sem_open("/sem_write", O_CREAT, 0644, 1);
	tmp->sem_forks = sem_open("/sem_forks", O_CREAT, 0644, nop);
	if (tmp->sem_write == SEM_FAILED || tmp->sem_forks == SEM_FAILED)
		return (printf("Failed To Open Semaphore\n"), -1);
	*monitor = tmp;
	return (0);
}

int	init_contain_bonus(t_philo **philo, int ac, char **av)
{
	t_philo	*tmp;

	tmp = (t_philo *)malloc(sizeof(t_philo));
	tmp->contain = (t_contain *)malloc(sizeof(t_contain));
	if (!tmp)
		return (printf("Allocation Failed\n"), -1);
	if (init_data(&tmp->contain->data, ac, av) == -1
		|| init_monitor(&tmp->contain->monitor, tmp->contain->data->nop) == -1)
		return (-1);
	tmp->pid = (pid_t *)malloc(sizeof(pid_t) * tmp->contain->data->nop);
	if (!tmp->pid)
		return (printf("Allocation Failed\n"), -1);
	tmp->isdied = false;
	tmp->eat_counter = 0;
	*philo = tmp;
	return (0);
}
