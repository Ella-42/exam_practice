/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:42:54 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/30 00:26:57 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	int pfd[2];
	int status;
	pipe(pfd);
	pid_t cmd1 = fork();
	if (!cmd1)
	{
		close(pfd[0]);
		dup2(pfd[1], 1);
		execve("/bin/ls", (char *[]){"/bin/ls", "-l", NULL}, env);
	}
	else
	{
		close(pfd[1]);
		waitpid(cmd1, &status, 0);
		dup2(pfd[0], 0);
		pipe(pfd);
		pid_t cmd2 = fork();
		if (!cmd2)
		{
			close(pfd[0]);
			dup2(pfd[1], 1);
			execve("/bin/cat", (char *[]){"/bin/cat", "-e", NULL}, env);
		}
		else
		{
			close(pfd[1]);
			waitpid(cmd2, &status, 0);
			dup2(pfd[0], 0);
			pid_t cmd3 = fork();
			if (!cmd3)
			{
				close(pfd[0]);
				execve("/bin/wc", (char *[]){"wc", NULL}, env);
			}
			else
			{
				waitpid(cmd3, &status, 0);
				printf("exit: %i\n", status);
			}
		}
	}
}
