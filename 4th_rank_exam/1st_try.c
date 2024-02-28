/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1st_try.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:48:19 by lpeeters          #+#    #+#             */
/*   Updated: 2024/02/28 16:23:38 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int	write_error(char *str)
{
	while (*str)
		write(2, str++, 1);
	return (1);
}

int	exec_cd(int ac, char **av)
{
	if (ac != 2)
		return (write_error("error: cd: bad arguments\n"));
	if (chdir(av[1]) < 0)
		return (write_error("error: cd: cannot change directory to "), write_error(av[1]), write_error("\n"));
	return (1);
}

int	exec(int i, char **av, char **env)
{
	int	has_pipe = av[i] && !strcmp(av[i], "|");
	int	fd[2];
	if (has_pipe && pipe(fd) < 0)
		return (write_error("error: fatal\n"));
	int	pid;
	if ((pid = fork()) < 0)
		return (write_error("error: fatal\n"));
	if (!pid)
	{
		av[i] = 0;
		if (has_pipe && (dup2(fd[1], 1) < 0 || close(fd[0]) < 0 || close(fd[1]) < 0))
			return (write_error("error: fatal\n"));
		execve(*av, av, env);
		return (write_error("error: cannot execute "), write_error(*av), write_error("\n"));
	}
	int	status;
	waitpid(pid, &status, 0);
	if (has_pipe && (dup2(fd[0], 0) < 0 || close(fd[0]) < 0 || close(fd[1]) < 0))
		return (write_error("error: fatal\n"));
	return (WIFEXITED(status) && WEXITSTATUS(status));
}

int	main(int ac, char **av, char **env)
{
	if (ac < 2)
		return (write(2, "error: invalid argument count\n", 30), 1);
	int i = 0;
	int error_status = 0;
	while (av[i] && av[++i])
	{
		av += i;
		i = 0;
		while (av[i] && strcmp(av[i], "|") && strcmp(av[i], ";"))
			i++;
		if (!strcmp(*av, "cd"))
			error_status = exec_cd(i, av);
		else if (i)
			error_status = exec(i, av, env);
	}
	return (error_status);
}
