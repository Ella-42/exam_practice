/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_serv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 21:47:23 by lpeeters          #+#    #+#             */
/*   Updated: 2025/09/08 23:52:44 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/ip.h>

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
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1 || bind(server_fd, (const struct sockaddr *)&server_address, sizeof(server_address)) || listen(server_fd, 10))
		error(0, server_fd);

	close(server_fd);
}
