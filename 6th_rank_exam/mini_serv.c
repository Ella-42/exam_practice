/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_serv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 21:47:23 by lpeeters          #+#    #+#             */
/*   Updated: 2025/09/11 03:44:16 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/ip.h>

typedef struct s_client
{
	size_t id;
	char buffer[1024];
}	t_client;

void error(const char *string, int fd)
{
	if (!string) write(STDERR_FILENO, "Fatal error\n", 12);
	else write(STDERR_FILENO, string, strlen(string));

	close(fd);
	exit(EXIT_FAILURE);
}

int main(int arguments, char *argument_list[])
{
	if (arguments < 2)
		error("Wrong number of arguments\n", -1);

	struct sockaddr_in server_address;
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(atoi(argument_list[1]));
	server_address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	int server_fd;
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1 || bind(server_fd, (const struct sockaddr *)&server_address, sizeof(server_address)) || listen(server_fd, SOMAXCONN))
		error(0, server_fd);

	fd_set fds, read_fds;
	FD_ZERO(&fds);
	FD_SET(server_fd, &fds);

	t_client clients[FD_SETSIZE];
	int ready, last_fd = server_fd;
	size_t last_id = 0;
	for (;;)
	{
		read_fds = fds;
		ready = select(last_fd + 1, &read_fds, NULL, NULL, NULL);

		for (int fd = 3; ready > 0; fd++)
		{
			if (!FD_ISSET(fd, &read_fds)) continue;

			ready--;

			if (fd == server_fd)
			{
				int client_fd = accept(server_fd, NULL, NULL);
				if (client_fd == -1) continue;

				if (client_fd > last_fd) last_fd = client_fd;
				FD_SET(client_fd, &fds);
				clients[client_fd].id = last_id++;
				memset(&(clients[client_fd].buffer), 0, 1024);

				write(STDOUT_FILENO, "New client accepted\n", 20);

				continue;
			}
		}
	}
}
