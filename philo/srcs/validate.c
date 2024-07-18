/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:16:31 by tkafanov          #+#    #+#             */
/*   Updated: 2024/07/18 17:29:14 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	validate_time_to_die(char *time_to_die)
{
	if (!contains_inly_digits(time_to_die))
		return (printf(ERR_MESS_DIE_DIGITS), false);
	if (ft_atoi(time_to_die) <= 0)
		return (printf(ERR_MESS_DIE), false);
	return (true);
}

bool	validate_time_to_eat(char *time_to_eat)
{
	if (!contains_inly_digits(time_to_eat))
		return (printf(ERR_MESS_EAT_DIGITS), false);
	if (ft_atoi(time_to_eat) <= 0)
		return (printf(ERR_MESS_EAT), false);
	return (true);
}

bool	validate_time_to_sleep(char *time_to_sleep)
{
	if (!contains_inly_digits(time_to_sleep))
		return (printf(ERR_MESS_SLEEP_DIGITS), false);
	if (ft_atoi(time_to_sleep) <= 0)
		return (printf(ERR_MESS_SLEEP), false);
	return (true);
}

bool	validate_number_of_meals(int argc, char **argv)
{
	if (argc == 6)
	{
		if (!contains_inly_digits(argv[5]))
			return (printf(ERR_MESS_MEALS_DIGITS), false);
		if (ft_atoi(argv[5]) <= 0)
			return (printf(ERR_MESS_MEALS), false);
	}
	return (true);
}

bool	validate_args(int argc, char **argv)
{
	bool	number;
	bool	time_to_die;
	bool	time_to_eat;
	bool	time_to_sleep;
	bool	number_of_meals;

	number = validate_number(argv[1]);
	time_to_die = validate_time_to_die(argv[2]);
	time_to_eat = validate_time_to_eat(argv[3]);
	time_to_sleep = validate_time_to_sleep(argv[4]);
	number_of_meals = validate_number_of_meals(argc, argv);
	return (true);
}
