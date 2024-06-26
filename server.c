/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:12:00 by ewoillar          #+#    #+#             */
/*   Updated: 2024/04/29 16:39:49 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minitalk.h"

char	*str;

void    receive_signal(int sig, siginfo_t *info, void *ucontext)
{
	static unsigned char    c = 0;
	static int              i = 0;

	(void)ucontext;
	if(!str)
		str = ft_strdup("");
	if (sig == SIGUSR1)
		c |= 1;
	i++;
	if (i == 8)
	{
		if (c == '\0')
		{
			ft_putstr_fd(str, 1);
			ft_putchar_fd('\n', 1);
			free(str);
			str = NULL;
		}
		else
			str = ft_strjoin(str, (char *)&c);
		//write(1, &c, 1);
		i = 0;
		c = 0;
	}
	c = c << 1;
	if (sig == SIGUSR1)
		kill(info->si_pid, SIGUSR1);
	else if (sig == SIGUSR2)
		kill(info->si_pid, SIGUSR2);

}

int		main(void)
{
	struct sigaction    sa;
	sigset_t			set;

	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	sigaddset(&set, SIGUSR2);
	sa.sa_handler = NULL;
	sa.sa_mask = set;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = receive_signal;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("Server PID: %d\n", getpid());
	while (1)
	{
		pause();
	}
	return (0);
}