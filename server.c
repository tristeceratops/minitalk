/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:12:00 by ewoillar          #+#    #+#             */
/*   Updated: 2024/04/24 18:09:06 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minitalk.h"

void    receive_signal(int sig, siginfo_t *info, void *ucontext)
{
	static unsigned char    c = 0;
	static int              i = 0;

	(void)ucontext;
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
		{
			write(1, "\n", 1);
			usleep(300);
			kill(info->si_pid, SIGUSR1);	
		}
		i = 0;
		c = 0;
	}
	usleep(300);
	kill(info->si_pid, SIGUSR2);
}

int		main(void)
{
	struct sigaction    sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = receive_signal;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	printf("Server PID: %d\n", getpid());
	while (1)
	{
		pause();
	}
	return (0);
}