/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 02:37:48 by fech-cha          #+#    #+#             */
/*   Updated: 2022/06/18 18:32:04 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

		i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0'
		&& s2[i] != '\0')
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i++] == '-' || !ft_strcmp(str, "0"))
		return (0);
	while (ft_isdigit(str[i]))
		i++;
	if (ft_strlen(str) == i)
		return (1);
	return (0);
}

int	check_errors(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (!ft_isnumber(av[i]) || ft_atoi(av[i]) > INT_MAX)
		{
			printf("Invalid Arguments!\n");
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
