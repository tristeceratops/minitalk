/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:12:00 by ewoillar          #+#    #+#             */
/*   Updated: 2024/04/24 13:40:21 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minitalk.h"

char	*g_str;

void    receive_signal(int signum)
{
	static char    c = 0;
	static int              i = 0;

	if (g_str == NULL)
		g_str = malloc(1);
	if (signum == SIGUSR1)
		c = c | 1;
	if (signum == SIGUSR1 && i != 7)
	    c = c << 1;
	if (signum == SIGUSR2 && i != 7)
	    c = c << 1;
	i++;
	if (i == 8)
	{
		g_str = ft_strjoin(g_str, &c);
		//write(1, &c, 1);
		if (c == '\0')
		{
			printf("%s\n", g_str);
			free(g_str);
			g_str = NULL;
		}
		i = 0;
		c = 0;
	}
}

int		main(void)
{
	struct sigaction    sa;

	sa.sa_handler = receive_signal;
	sa.sa_flags = SA_SIGINFO;
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