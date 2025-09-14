#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct s_client
{
	size_t id;
	char buf[1024];
	uint16_t end;
}	t_client;

void err(const char* msg, int fd)
{
	if (!msg) write(STDERR_FILENO, "Fatal error", 11);
	else write(STDERR_FILENO, msg, strlen(msg));
	write(STDERR_FILENO, "\n", 1);

	close(fd);
	exit(EXIT_FAILURE);
}

void asend(int from, int lfd, fd_set fds, const char *msg)
{
	for (int fd = 4; fd <= lfd; fd++)
		if (fd != from && FD_ISSET(fd, &fds))
			write(fd, msg, strlen(msg));
}

bool emsg(char *buf, char *msg, uint16_t *end)
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

int main(int ac, char *av[])
{
	if (ac < 2)
		err("Wrong number of arguments", -1);

	struct sockaddr_in s;
	memset(&s, '\0', sizeof(s));
	s.sin_family = AF_INET;
	s.sin_port = htons(atoi(av[1]));
	s.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	int sfd;
	if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 || bind(sfd, (const struct sockaddr *)&s, sizeof(s)) || listen(sfd, SOMAXCONN))
		err(0, sfd);

	int lfd = sfd;
	fd_set fds, rfds;
	FD_ZERO(&fds);
	FD_SET(sfd, &fds);

	t_client clients[FD_SETSIZE];
	size_t id = 0;
	for (;;)
	{
		rfds = fds;
		int r = select(lfd + 1, &rfds, NULL, NULL, NULL);

		for (int fd = 3; r > 0; fd++)
		{
			if (!FD_ISSET(fd, &rfds)) continue;

			r--;

			if (fd == sfd)
			{
				int cfd = accept(sfd, NULL, NULL);
				if (cfd == -1) continue;

				if (cfd > lfd) lfd = cfd;
				FD_SET(cfd, &fds);
				clients[cfd].id = id;
				memset(clients[cfd].buf, '\0', 1024);
				clients[cfd].end = 0;

				sprintf(clients[0].buf, "server: client %lu just arrived\n", id++);
				asend(cfd, lfd, fds, clients[0].buf);

				continue;
			}

			short in = recv(fd, clients[fd].buf + clients[fd].end, 1024 - clients[fd].end, 0);
			if (in == -1) continue;

			if (in == 0)
			{
				FD_CLR(fd, &fds);
				close(fd);

				sprintf(clients[2].buf, "server: client %lu just left\n", clients[fd].id);
				asend(fd, lfd, fds, clients[2].buf);

				continue;
			}

			char msg[2048];
			while (emsg(clients[fd].buf, clients[1].buf, &(clients[fd].end)))
			{
				sprintf(msg, "client %lu: %s\n", clients[fd].id, clients[1].buf);
				asend(fd, lfd, fds, msg);
			}
		}
	}
}
