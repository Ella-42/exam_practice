#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <netinet/ip.h>

typedef struct s_client
{
	size_t id;
	char buf[100001];
	uint32_t end;
}	t_client;

void err(const char *msg, short fd)
{
	if (!msg) write(STDERR_FILENO, "Fatal error", 11);
	else write(STDERR_FILENO, msg, strlen(msg));
	write(STDERR_FILENO, "\n", 1);

	if (fd > 0) close(fd);
	exit(EXIT_FAILURE);
}

void allsend(short sentfd, short servfd, short lastfd, fd_set allfds, const char *msg)
{
	for (short fd = servfd + 1; fd <= lastfd; fd++)
		if (fd != sentfd && FD_ISSET(fd, &allfds))
			send(fd, msg, strlen(msg), MSG_NOSIGNAL);
}

bool getmsg(char *buf, char *msg, uint32_t *end)
{
	memset(msg, '\0', strlen(msg));

	uint32_t i;
	for (i = 0; buf[i] && buf[i] != '\n'; i++)
		msg[i] = buf[i];

	if (buf[i] != '\n')
		return *end = i, false;

	i++;
	uint32_t j;
	for (j = 0; buf[i]; j++, i++)
		buf[j] = buf[i];
	memset(buf + j, '\0', i - j);

	return *end = j, true;
}

t_client clients[FD_SETSIZE];
int main(int ac, char *av[])
{
	if (ac < 2)
		err("Wrong number of arguments", -1);

	short servfd;
	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(atoi(av[1]));
	sin.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	if ((servfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 || bind(servfd, (const struct sockaddr *)&sin, sizeof(sin)) || listen(servfd, SOMAXCONN))
		err(0, servfd);

	short lastfd = servfd;
	fd_set allfds, readfds;
	FD_ZERO(&allfds);
	FD_SET(servfd, &allfds);
	size_t id = 0;
	for (;;)
	{
		short ready;
		readfds = allfds;
		if ((ready = select(lastfd + 1, &readfds, 0, 0, 0)) == -1) continue;

		for (short fd = servfd; ready > 0; fd++)
		{
			if (!FD_ISSET(fd, &readfds)) continue;
			ready--;

			if (fd == servfd)
			{
				short clientfd;
				if ((clientfd = accept(servfd, 0, 0)) == -1) continue;

				char msg[50];
				sprintf(msg, "server: client %lu just arrived\n", id);
				allsend(clientfd, servfd, lastfd, allfds, msg);

				if (clientfd > lastfd) lastfd = clientfd;
				FD_SET(clientfd, &allfds);
				clients[clientfd].id = id++;
				if (clients[clientfd].end)
				{
					memset(clients[clientfd].buf, '\0', clients[clientfd].end);
					clients[clientfd].end = 0;
				}

				continue;
			}

			int recvd = 0;
			if (clients[fd].end != 100001 && (recvd = recv(fd, clients[fd].buf + clients[fd].end, 100001 - clients[fd].end, 0)) == -1) continue;

			if (recvd == 0)
			{
				if (clients[fd].end == 100001)
					send(fd, "Failed to send: buffer limit exceeded (100001)\n", 47, MSG_NOSIGNAL);

				char msg[47];
				sprintf(msg, "server: client %lu just left\n", clients[fd].id);
				allsend(fd, servfd, lastfd, allfds, msg);

				if (fd == lastfd) lastfd--;
				FD_CLR(fd, &allfds);
				close(fd);

				continue;
			}

			char msg[100031];
			while (getmsg(clients[fd].buf, clients[0].buf, &(clients[fd].end)))
			{
				sprintf(msg, "client %lu: %s\n", clients[fd].id, clients[0].buf);
				allsend(fd, servfd, lastfd, allfds, msg);
			}
		}
	}
}
