#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

#pragma GCC diagnostic ignored "-Wpedantic"

/**
 * main - Entry point
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
	int sockid = socket(AF_INET, SOCK_STREAM, getprotobyname("tcp")->p_proto);
	if (-1 == sockid)
	{
		perror("failed to create socket");
		return (EXIT_FAILURE);
	}

	struct sockaddr_in addrport = (struct sockaddr_in){AF_INET, htons(12345), {htonl(INADDR_ANY)}, {0}};
	if (-1 == bind(sockid, (const struct sockaddr *)&addrport, sizeof(addrport)))
	{
		perror("failed to bind socket");
		return (EXIT_FAILURE);
	}
	if (-1 == listen(sockid, 1))
	{
		perror("failed to listen on port 12345");
		return (EXIT_FAILURE);
	}

	puts("Server listening on port 12345");
	while (1);

	return (EXIT_SUCCESS);
}
