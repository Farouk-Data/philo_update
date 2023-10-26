/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 02:37:51 by fech-cha          #+#    #+#             */
/*   Updated: 2022/06/17 22:10:16 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->cont->data->n_philos)
	{
		free(philo + i);
		i++;
	}
	free(philo);
}

int	main(int argc, char **argv)
{
	int		i;
	t_cont	*cont;

	i = 0;
	if ((argc != 5 && argc != 6))
		return (printf("Too Many Or Less Arguments!\n"), 0);
	if (check_errors(argv))
		return (EXIT_FAILURE);
	if (init(&cont, argc, argv) == -1)
		return (-1);
	if (execution(cont->philo) == -1)
		return (-1);
	free(cont->data);
	free(cont->moni);
	ft_free(cont->philo);
	free(cont);
	return (0);
}
