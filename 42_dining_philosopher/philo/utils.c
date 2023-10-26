/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 02:38:05 by fech-cha          #+#    #+#             */
/*   Updated: 2022/06/17 20:57:28 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday (&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	retard_proc(int64_t time_in_ms, t_philo *philo)
{
	int64_t	start_time;

	start_time = get_time();
	while (philo->cont->moni->status)
	{
		if (get_time() - start_time >= time_in_ms)
			break ;
		usleep(500);
	}
}

void	print_action(t_philo *philo, char *str)
{
	pthread_mutex_lock (&philo->cont->moni->mutex_print);
	if (philo->cont->moni->status)
		printf("|%7lld|--|%d|--%s\n", \
				get_time() - philo->cont->moni->start, philo->philosopher, str);
	pthread_mutex_unlock(&philo->cont->moni->mutex_print);
}
