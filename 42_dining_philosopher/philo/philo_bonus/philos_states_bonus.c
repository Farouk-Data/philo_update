/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_states_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 02:38:35 by fech-cha          #+#    #+#             */
/*   Updated: 2022/06/17 00:08:47 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_sleep(long long time)
{
	long long	t;

	t = current_timestamp();
	while (1)
	{
		if (current_timestamp() - t >= time)
			break ;
		usleep(100);
	}
}

void	print_state(t_philo *philo, char *str)
{
	sem_wait(&philo->contain->monitor->sem_printf);
	if (philo->contain->monitor->status)
		printf("\e[3;4;37m[%7lld \e[4;3;2;33mms]\e[0m\e[0m\t\e[3;4;37m[%d]\e[0m\t%s\n",
			current_timestamp()
			- philo->contain->monitor->start_time, philo->philo_number, str);
	sem_post(&philo->contain->monitor->sem_printf);
}

void	philo_end(t_philo **philo)
{
	t_philo	*tmp;
	int		i;
	int		flag;

	tmp = *philo;
	i = 0;
	while (i < tmp->contain->data->nop)
	{
		waitpid(-1, &flag, 0);
		if (flag != 0)
		{
			i = -1;
			while (++i < tmp->contain->data->nop)
				kill(tmp->pid[i], SIGKILL);
			break ;
		}
		i++;
	}
	sem_close(tmp->contain->monitor->sem_write);
	sem_close(tmp->contain->monitor->sem_forks);
	sem_unlink("/sem_write");
	sem_unlink("/sem_forks");
	free(tmp->pid);
	free(tmp);
}

void	*monitor(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (philo->contain->monitor->status)
	{
		usleep(100);
		if (current_timestamp() - philo->last_meal_time
			> philo->contain->data->time_to_die)
		{
			philo->isdied = true;
			sem_wait(philo->contain->monitor->sem_write);
			print_state(philo, "is died");
			philo->contain->monitor->status = false;
			break ;
		}
		if (philo->contain->data->nom != -1 && philo->eat_counter
			>= philo->contain->data->nom)
		{
			philo->contain->monitor->status = false;
			break ;
		}
	}
	if (philo->isdied)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

int	philo_start_bonus(t_philo *philo)
{
	if (pthread_create(&philo->contain->monitor->thread_monitor
			, NULL, monitor, philo))
		return (printf("Failed To Create Thread!!!\n"), -1);
	if (philo->philo_number % 2)
		usleep(1000);
	while (true)
	{
		print_state(philo, "is thinking");
		sem_wait(philo->contain->monitor->sem_forks);
		print_state(philo, "has taken a fork");
		sem_wait(philo->contain->monitor->sem_forks);
		print_state(philo, "has taken a fork");
		print_state(philo, "is eating");
		ft_sleep(philo->contain->data->time_to_eat);
		philo->last_meal_time = current_timestamp();
		sem_post(philo->contain->monitor->sem_forks);
		sem_post(philo->contain->monitor->sem_forks);
		philo->eat_counter++;
		print_state(philo, "is sleeping");
		ft_sleep(philo->contain->data->time_to_sleep);
	}
	if (pthread_join(philo->contain->monitor->thread_monitor, NULL))
		return (printf("Failed To Join Thread!!!\n"), -1);
	return (0);
}
