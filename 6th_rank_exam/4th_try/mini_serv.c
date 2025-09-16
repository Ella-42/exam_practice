#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <netinet/ip.h>

typedef struct s_client
{
	size_t id;
	char buf[1024];
	uint16_t end;
}	t_client;

void err(const char *msg, int fd)
{
	if (!msg) write(STDERR_FILENO, "Fatal error", 11);
	else write(STDERR_FILENO, msg, strlen(msg));
	write(STDERR_FILENO, "\n", 1);

	close(fd);
	exit(EXIT_FAILURE);
}

void allsend(int sentfd, int lastfd, int servfd, fd_set allfds, const char *msg)
{
	for (int fd = servfd + 1; fd <= lastfd; fd++)
		if (fd != sentfd && FD_ISSET(fd, &allfds))
			write(fd, msg, strlen(msg));
}

bool getmsg(char *buf, char *msg, uint16_t *end)
{
	memset(msg, '\0', 1024);

	uint16_t i;
	for (i = 0; buf[i] && buf[i] != '\n'; i++)
		msg[i] = buf[i];

	if (buf[i] != '\n')
		return *end = i, false;

	i++;
	uint16_t j;
	for (j = 0; buf[i]; j++, i++)
		buf[j] = buf[i];
	memset(buf + j, '\0', 1024 - j);

	return *end = j, true;
}

int main(int argc, char *argv[])
{
	if (argc < 2)
		err("Wrong number of arguments", -1);

	int servfd;
	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(atoi(argv[1]));
	sin.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	if ((servfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 || bind(servfd, (const struct sockaddr *)&sin, sizeof(sin)) || listen(servfd, SOMAXCONN))
	err(0, servfd);

	int lastfd = servfd;
	fd_set allfds, readfds;
	FD_ZERO(&allfds);
	FD_SET(servfd, &allfds);
	t_client clients[FD_SETSIZE];
	size_t id = 0;
	for (;;)
	{
		readfds = allfds;
		int ready;
		if ((ready = select(lastfd + 1, &readfds, 0, 0, 0)) == -1) continue;

		for (int fd = servfd; ready > 0; fd++)
		{
			if (!FD_ISSET(fd, &readfds)) continue;
			ready--;

			if (fd == servfd)
			{
				int clientfd;
				if ((clientfd = accept(servfd, 0, 0)) == -1) continue;

				if (clientfd > lastfd) lastfd = clientfd;
				FD_SET(clientfd, &allfds);
				clients[clientfd].id = id;
				memset(clients[clientfd].buf, '\0', 1024);
				clients[clientfd].end = 0;

				sprintf(clients[0].buf, "server: client %lu just arrived\n", id++);
				allsend(clientfd, lastfd, servfd, allfds, clients[0].buf);

				continue;
			}

			int recvd;
			if ((recvd = recv(fd, clients[fd].buf + clients[fd].end, 1024 - clients[fd].end, 0)) == -1) continue;

			if (recvd == 0)
			{
				FD_CLR(fd, &allfds);
				close(fd);

				sprintf(clients[2].buf, "server: client %lu just left\n", clients[fd].id);
				allsend(fd, lastfd, servfd, allfds, clients[2].buf);

				continue;
			}

			char msg[2048];
			while(getmsg(clients[fd].buf, clients[1].buf, &(clients[fd].end)))
			{
				sprintf(msg, "client %lu: %s\n", clients[fd].id, clients[1].buf);
				allsend(fd, lastfd, servfd, allfds, msg);
			}
		}
	}
}
