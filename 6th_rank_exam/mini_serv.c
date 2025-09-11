/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_serv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 21:47:23 by lpeeters          #+#    #+#             */
/*   Updated: 2025/09/11 23:50:16 by lpeeters         ###   ########.fr       */
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

void all_send(int sender_fd, fd_set fds, int last_fd, const char *string)
{
	for (int fd = 4; fd <= last_fd; fd++)
		if (fd != sender_fd && FD_ISSET(fd, &fds)) write(fd, string, strlen(string));
}

int extract_message(char *buffer, char *message)
{
	for (uint32_t i = 0; buffer[i]; i++)
	{
		if (buffer[i] == '\n')
		{
			strcpy(message, buffer);
			message[i] = '\0';
			strcpy(buffer, buffer + i + 1);
			return (1);
		}
	}
	return (0);
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
				clients[client_fd].id = last_id;
				memset(&(clients[client_fd].buffer), 0, 1024);

				sprintf(clients[0].buffer, "server: client %lu just arrived\n", last_id++);
				all_send(client_fd, fds, last_fd, clients[0].buffer);

				continue;
			}

			short received = recv(fd, clients[fd].buffer, 1024, 0);
			if (received == -1) continue;

			if (received == 0)
			{
				FD_CLR(fd, &fds);
				close(fd);

				sprintf(clients[2].buffer, "server: client %lu just left\n", clients[fd].id);
				all_send(fd, fds, last_fd, clients[2].buffer);

				continue;
			}

			char message[2048];
			while (extract_message(clients[fd].buffer, clients[1].buffer))
			{
				sprintf(message, "client %lu: %s\n", clients[fd].id, clients[1].buffer);
				all_send(fd, fds, last_fd, message);
			}
		}
	}
}
