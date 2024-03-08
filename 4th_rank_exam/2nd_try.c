/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2nd_try.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:11:51 by lpeeters          #+#    #+#             */
/*   Updated: 2024/02/29 15:20:19 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int	err(char *str)
{
	while (*str)
		write(2, str++, 1);
	return (1);
}

int	cd(int i, char **av)
{
	if (i != 2)
		return (err("error: cd: bad arguments\n"));
	if (chdir(av[1]) < 0)
		return (err("error: cd: cannot change directory to "), err(av[1]), err("\n"));
	return (0);
}

int	exec(int i, char **av, char **env)
{
	int fd[2];
	int status;
	int has_pipe = av[i] && !strcmp(av[i], "|");
	if (has_pipe && pipe(fd) < 0)
		return (err("error: fatal\n"));
	int pid;
	if ((pid = fork()) < 0)
		return (err("error: fatal\n"));
	if (!pid)
	{
		av[i] = 0;
		if (has_pipe && (dup2(fd[1], 1) < 0 || close(fd[0] < 0) || close(fd[1]) < 0))
			return (err("error: fatal\n"));
		execve(*av, av, env);
		return (err("error: cannot execute "), err(*av), err("\n"));
	}
	waitpid(pid, &status, 0);
	if (has_pipe && (dup2(fd[0], 0) < 0 || close(fd[0]) < 0 || close(fd[1]) < 0))
		return (err("error: fatal\n"));
	return (WIFEXITED(status) && WEXITSTATUS(status));
}

int	main(int ac, char **av, char **env)
{
	if (ac < 2)
		return (1);
	int i = 0;
	int status = 0;
	while (av[i] && av[++i])
	{
		av += i;
		i = 0;
		while (av[i] && strcmp(av[i], "|") && strcmp(av[i], ";"))
			i++;
		if (!strcmp(*av, "cd"))
			status = cd(i, av);
		else if (i)
			status = exec(i, av, env);
	}
	return (status);
}
