/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:16:41 by tkafanov          #+#    #+#             */
/*   Updated: 2024/07/18 17:29:54 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// int counter = 0;
// pthread_mutex_t lock;

// void	*print()
// {
// 	int i = 0;
// 	while (i < 1000000)
// 	{
// 		pthread_mutex_lock(&lock);
// 		i++;
// 		counter++;
// 		pthread_mutex_unlock(&lock);
// 	}
// 	// printf("Hello from threads\n");
// 	// usleep(1);
// 	// printf("Process ID: %d\n", getpid());
// 	return (SUCCESS);
// }

int	main(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		if (!validate_args(argc, argv))
			return (ERROR);
	}
	else
		return (printf("Error! Wrong amount of arguments!\n"), ERROR);
	// pthread_t t1, t2;
	// pthread_mutex_init(&lock, NULL);
	// if (pthread_create(&t1, NULL, &print, NULL))
	// 	return (ERROR);
	// if (pthread_create(&t2, NULL, &print, NULL))
	// 	return (ERROR);
	// if (pthread_join(t1, NULL))
	// 	return (ERROR);
	// if (pthread_join(t2, NULL))
	// 	return (ERROR);
	// pthread_mutex_destroy(&lock);
	// printf("counter = %d\n", counter);
	return (SUCCESS);
}
