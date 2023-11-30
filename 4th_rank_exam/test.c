/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:42:54 by lpeeters          #+#    #+#             */
/*   Updated: 2023/12/01 00:21:48 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int	main(int ac, char **av, char **env)
{
	pid_t	cmd1;
	pid_t	cmd2;
	pid_t	cmd3;
	int		pfd[2];
	int		status;

	(void)ac;
	(void)av;
	pipe(pfd);
	cmd1 = fork();
	if (!cmd1)
	{
		close(pfd[0]);
		dup2(pfd[1], 1);
		close(pfd[1]);
		execve("/bin/ls", (char *[]){"ls", NULL}, env);
	}
	else
	{
		waitpid(cmd1, &status, 0);
		close(pfd[1]);
		dup2(pfd[0], 0);
		close(pfd[0]);
		pipe(pfd);
		cmd2 = fork();
		if (!cmd2)
		{
			close(pfd[0]);
			dup2(pfd[1], 1);
			close(pfd[1]);
			execve("/bin/cat", (char *[]){"/bin/cat", "-e", NULL}, env);
		}
		else
		{
			waitpid(cmd1, &status, 0);
			close(pfd[1]);
			dup2(pfd[0], 0);
			close(pfd[0]);
			cmd3 = fork();
			if (!cmd3)
			{
				execve("/bin/ls", (char *[]){"ls", NULL}, env);
			}
			else
			{
				waitpid(cmd3, &status, 0);
				close(pfd[1]);
				printf("exit: %i\n", status);
			}
		}
	}
}
