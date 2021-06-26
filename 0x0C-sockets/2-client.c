#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#pragma GCC diagnostic ignored "-Wpedantic"
#define TRY(op, msg) do {if ((op) == -1) {perror(msg); return (EXIT_FAILURE);}} while (0)

/**
 * main - Entry point
 * @argc: int argument count
 * @argv: char pointer argument array
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(int argc, char *argv[])
{

	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <host> <port>\n", argv[0]);
		return (EXIT_FAILURE);
	}

	const char *host = argv[1], *port = argv[2];

	struct addrinfo hints;
	struct addrinfo *servinfo;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	int status;
	if ((status = getaddrinfo(host, port, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
		exit(EXIT_FAILURE);
	}

	int sockid;
	TRY(sockid = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol),
 	    "failed to create socket");
	TRY(connect(sockid, servinfo->ai_addr, servinfo->ai_addrlen), "failed to connect");

	printf("Connected to %s:%s\n", host, port);

	freeaddrinfo(servinfo);
	TRY(close(sockid), "failed to close socket");

	return (EXIT_SUCCESS);
}
