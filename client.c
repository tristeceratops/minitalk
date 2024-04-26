/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:12:02 by ewoillar          #+#    #+#             */
/*   Updated: 2024/04/26 14:21:14 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int		confirmation;

void    receive_signal(int sig, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (sig == SIGUSR1 || sig == SIGUSR2)
		confirmation = 1;
}

void    send_signal(int pid, unsigned char c)
{
    int     i;
    unsigned char   temp_char;

    i = 8;
    temp_char = c;
    while (i > 0)
    {
		confirmation = 0;
        temp_char = c >> --i;
        if (temp_char % 2 == 0)
		{
            kill(pid, SIGUSR2);
			while (confirmation == 0)
				;
		}
        else
		{
            kill(pid, SIGUSR1);
			while (confirmation == 0)
				;
		}
    }
}

void	ft_check_parameters(int argc, char *argv[])
{
	int		index;

	index = 0;
	if (argc != 3)
		exit(ft_printf("Number of arguments invalid\n"));
	while (argv[1][index] != '\0')
	{
		if (!ft_isdigit(argv[1][index]))
			exit(ft_printf("Error: Invalid PID\n"));
		index++;
	}
	
}

int		main(int argc, char **argv)
{
	int		i;
	int		pid;
	char	*str;
	struct sigaction    sa;
	sigset_t			set;

	ft_check_parameters(argc, argv);
	sigemptyset(&set);
	sa.sa_handler = NULL;
	sa.sa_mask = set;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = receive_signal;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	pid = ft_atoi(argv[1]);
	str = argv[2];
	i = 0;
	while (str[i])
	{
		send_signal(pid, str[i++]);
	}
	send_signal(pid, '\0');
	confirmation = 0;
	return (0);
}