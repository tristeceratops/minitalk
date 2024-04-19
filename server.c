/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:12:00 by ewoillar          #+#    #+#             */
/*   Updated: 2024/04/19 17:39:15 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_SOURCE
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void catcher(int signum) {
  puts("catcher() has gained control");
}

void catcher_2(int signum) {
  puts("2");
}

int main() {
  struct   sigaction sact;
  sigset_t sigset;

  sigemptyset(&sact.sa_mask);
  sact.sa_flags = 0;
  sact.sa_handler = catcher;
  sigaction(SIGUSR1, &sact, NULL);

  puts("before first kill()");
  kill(getpid(), SIGUSR1);
  puts("before second kill()");

  sigemptyset(&sigset);
  sigaddset(&sigset, SIGUSR1);
  sigprocmask(SIG_SETMASK, &sigset, NULL);
  sact.sa_handler = catcher_2;
  sigaction(SIGUSR2, &sact, NULL);

  kill(getpid(), SIGUSR1);
  kill(getpid(), SIGUSR2);
  puts("after second kill()");
}