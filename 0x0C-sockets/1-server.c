#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#pragma GCC diagnostic ignored "-Wpedantic"
#define TRY(op, msg) do {if ((op) == -1) {perror(msg); return (EXIT_FAILURE);}} while (0)

/**
 * main - Entry point
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
	int listen_sockid;
	TRY(listen_sockid = socket(AF_INET, SOCK_STREAM, getprotobyname("tcp")->p_proto),
 	    "failed to create socket");

	struct sockaddr_in addrport = (struct sockaddr_in){AF_INET, htons(12345), {htonl(INADDR_ANY)}, {0}};
	TRY(bind(listen_sockid, (const struct sockaddr *)&addrport, sizeof(addrport)),
	    "failed to bind socket");
	TRY(listen(listen_sockid, 1), "failed to listen on port 12345");

	puts("Server listening on port 12345");

	struct sockaddr_in client_addr;
	socklen_t client_addr_len = sizeof(client_addr);
	int data_sockid;
	TRY(data_sockid = accept(listen_sockid, (struct sockaddr *)&client_addr, &client_addr_len),
	    "failed to accept client connection");

	char buf[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &client_addr.sin_addr, buf, INET_ADDRSTRLEN);
	printf("Client connected: %s\n", buf);

	TRY(close(listen_sockid), "failed to close socket");
	TRY(close(data_sockid), "failed to close socket");

	return (EXIT_SUCCESS);
}
