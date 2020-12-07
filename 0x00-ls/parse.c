#include "hls.h"


/**
 * parse_args - parses args
 * @args_in: input args
 * @args_out: output args
 * @options: bitflags
 */
void parse_args(char **args_in, char **args_out, option_t *options)
{
	char *arg = NULL;
	size_t i = 0;

	while ((arg = args_in[i]))
	{
		#if TESTING
		printf("arg=%s\n", arg);
		#endif
		if (arg[0] == '-' && _strcmp(arg, "-") != 0)
		{
			parse_opts(arg, options);
		}
		else
		{
			args_out[i] = arg;
		}
		++i;
	}
}

/**
 * parse_opts - parses opts
 * @arg: arg containing option flag string
 * @options: options bitflag
 */
void parse_opts(char *arg, option_t *options)
{

	while (*++arg)
	{
		#if TESTING
		putchar(*arg);
		putchar('=');
		dbg_print_binary((unsigned char)*options);
		putchar('\n');
		#endif
		switch (*arg)
		{
		case '1':
			*options |= ONEPERLINE;
			#if TESTING
			SCREAM("made it to case '1' in `parse_opts`");
			#endif
			break;
		case 'a':
			*options |= ALL;
			break;
		case 'A':
			*options |= ALMOSTALL;
			break;
		case 'h':
			*options |= HUMAN;
			break;
		case 'l':
			*options |= LISTING;
			break;
		default:
			#if TESTING
			SCREAM("TODO: handle bad flag");
			#endif /* TESTING */
			fprintf(stderr, "Unknown flag\n");
			exit(2);
			break;
		}
	}
}
