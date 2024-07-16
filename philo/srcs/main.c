/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:16:41 by tkafanov          #+#    #+#             */
/*   Updated: 2024/07/16 15:53:24 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*print()
{
	printf("Hello from threads\n");
	usleep(1);
	printf("Process ID: %d\n", getpid());
	return (SUCCESS);
}

int	main()
{
	pthread_t t1, t2;
	if (pthread_create(&t1, NULL, &print, NULL))
		return (ERROR);
	if (pthread_create(&t2, NULL, &print, NULL))
		return (ERROR);
	if (pthread_join(t1, NULL))
		return (ERROR);
	if (pthread_join(t2, NULL))
		return (ERROR);
	return (SUCCESS);
}
