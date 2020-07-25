#include "hls.h"


/**
 * _strcmp - compares two imput string s1 and s2. It
 **          returns an integer less than, equal to,
 **          or greater than zero if s1 is found,
 **          respectively, to be less than, to match,
 **          or be greater than s2.
 * @s1: pointer to string.
 * @s2: pointer to string
 *
 * Return: 0 if s1 matches s2, else a negative int if
 *         s1 is less than s2, else a positive int.
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

/**
 * _strcoll - wrapper for _strcmp intended to handle
 **	special cases via the option_t option flag (TODO).
 * @s1: pointer to string.
 * @s2: pointer to string
 *
 * Return: 0 if s1 matches s2, else a negative int if
 *         s1 is less than s2, else a positive int.
 */
int _strcoll(char *s1, char *s2)
{
	return (_strcmp(s1, s2));
}

