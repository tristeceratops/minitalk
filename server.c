/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:12:00 by ewoillar          #+#    #+#             */
/*   Updated: 2024/04/24 16:49:19 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_SOURCE
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void    receive_signal(int sig)
{
	static unsigned char    c = 0;
	static int              i = 0;
	if (sig == SIGUSR1)
		c = c | 1;
	if (sig == SIGUSR1 && i != 7)
	    c = c << 1;
	if (sig == SIGUSR2 && i != 7)
	    c = c << 1;
	i++;
	if (i == 8)
	{
		write(1, &c, 1);
		if (c == '\0')
			write(1, "\n", 1);
		i = 0;
		c = 0;
	}
}

int		main(void)
{
	struct sigaction    sa;

	sa.sa_handler = receive_signal;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	printf("Server PID: %d\n", getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}