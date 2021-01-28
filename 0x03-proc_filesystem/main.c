#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
	char *s;
	unsigned long int i;

	i = 0;
	s = strdup("Holberton");
	while (s)
	{
		printf("[%lu] %s\n", i, s);
		sleep(1);
		i++;
	}
	return (0);
}
