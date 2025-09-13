#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void err(const char* message, int fd)
{
	if (!message)
		write(STDERR_FILENO, "Fatal error", 11);
	else
		write(STDERR_FILENO, message, strlen(message));
	write(STDERR_FILENO, "\n", 1);

	close(fd);
	exit(EXIT_FAILURE);
}

int main(int ac, char *av[])
{
	(void)av;
	if (ac < 2)
		err("Wrong number of arguments", -1);
}
