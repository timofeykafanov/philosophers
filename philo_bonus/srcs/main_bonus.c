/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:33:16 by tkafanov          #+#    #+#             */
/*   Updated: 2024/07/16 16:49:10 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo_bonus.h"

int	main()
{
	int	pid;

	pid = fork();
	// pid = fork();
	// pid = fork();
	if (pid == -1)
		return ERROR;
	if (pid == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			printf("Hello from processes\n");
			printf("Process ID: %d\n", getpid());
			wait(NULL);
		}
		else
		{
			printf("Hello from processes\n");
			printf("Process ID: %d\n", getpid());
		}
		wait(NULL);
	}
	else
	{
		printf("Hello from processes\n");
		printf("Process ID: %d\n", getpid());
	}
	return (SUCCESS);
}
