/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:17:22 by tkafanov          #+#    #+#             */
/*   Updated: 2024/10/03 12:44:58 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	contains_only_digits(char *number)
{
	int	i;

	i = 0;
	while (number[i])
	{
		if (!ft_isdigit(number[i]) && number[i] != '-')
			return (false);
		i++;
	}
	return (true);
}

bool	validate_number(char *number)
{
	if (!contains_only_digits(number))
		return (printf(ERR_MESS_NUM_DIGITS), false);
	if (ft_atoi(number) <= 0 || ft_atoi(number) > 200)
		return (printf(ERR_MESS_NUMBER), false);
	return (true);
}
