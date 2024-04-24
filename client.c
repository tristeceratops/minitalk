/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:12:02 by ewoillar          #+#    #+#             */
/*   Updated: 2024/04/24 15:24:26 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void    send_signal(int pid, unsigned char c)
{
    int     i;
    unsigned char   temp_char;

    i = 8;
    temp_char = c;
    while (i > 0)
    {
        i--;
        temp_char = c >> i;
        if (temp_char % 2 == 0)
            kill(pid, SIGUSR2);
        else
            kill(pid, SIGUSR1);
		usleep(200);
    }
}

int		main(int argc, char **argv)
{
	int		i;
	int		pid;
	char	*str;

	if (argc != 3)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	str = argv[2];
	i = 0;
	while (str[i])
	{
		send_signal(pid, str[i++]);
	}
	send_signal(pid, '\0');
	return (0);
}