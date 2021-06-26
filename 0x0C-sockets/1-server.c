#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#pragma GCC diagnostic ignored "-Wpedantic"
#define TRY(op, msg) do {op; perror(msg); return (EXIT_FAILURE)} while (0)

/**
 * main - Entry point
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
	int listen_sockid = socket(AF_INET, SOCK_STREAM, getprotobyname("tcp")->p_proto);
	if (-1 == listen_sockid)
	{
		perror("failed to create socket");
		return (EXIT_FAILURE);
	}

	struct sockaddr_in addrport = (struct sockaddr_in){AF_INET, htons(12345), {htonl(INADDR_ANY)}, {0}};
	if (-1 == bind(listen_sockid, (const struct sockaddr *)&addrport, sizeof(addrport)))
	{
		perror("failed to bind socket");
		return (EXIT_FAILURE);
	}
	if (-1 == listen(listen_sockid, 1))
	{
		perror("failed to listen on port 12345");
		return (EXIT_FAILURE);
	}

	puts("Server listening on port 12345");

	struct sockaddr_in client_addr;
	socklen_t client_addr_len = sizeof(client_addr);
	int data_sockid = accept(listen_sockid, (struct sockaddr *)&client_addr, &client_addr_len);
	if (-1 == data_sockid)
	{
		perror("failed to accept client connection");
		return (EXIT_FAILURE);
	}

	char buf[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &client_addr.sin_addr, buf, INET_ADDRSTRLEN);
	printf("Client connected: %s\n", buf);

	if (-1 == close(listen_sockid) || -1 == close(data_sockid))
	{
		perror("failed to close socket");
		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}
