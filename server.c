/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:12:00 by ewoillar          #+#    #+#             */
/*   Updated: 2024/04/24 19:14:02 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minitalk.h"

char *str;

void    receive_signal(int sig, siginfo_t *info, void *ucontext)
{
	static unsigned char    c = 0;
	static int              i = 0;

	(void)ucontext;
	if (str == NULL)
		str = malloc(1);
	if (sig == SIGUSR1)
		c = c | 1;
	if (sig == SIGUSR1 && i != 7)
	    c = c << 1;
	if (sig == SIGUSR2 && i != 7)
	    c = c << 1;
	i++;
	kill(info->si_pid, SIGUSR2);
	usleep(50);
	if (i == 8)
	{
		char temp[2];
		temp[0] = c;
		temp[1] = '\0';
		str = ft_strjoin(str, temp);
		//write(1, &c, 1);
		if (c == '\0')
		{
			ft_putstr_fd(str, 1);
			write(1, "\n", 1);
			kill(info->si_pid, SIGUSR1);	
			usleep(50);
			free(str);
			str = NULL;
		}
		i = 0;
		c = 0;
	}
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