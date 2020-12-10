#include "hls.h"
#include "debug.h"


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
		dbg_printf("parse_args:\n\targ = %s\n", arg);

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
		/* dbg_printf("%c = ", *arg); */
		/* dbg_print_binary((unsigned char)*options); */
		switch (*arg)
		{
		case '1':
			*options |= ONEPERLINE;
			dbg_printf("parse_opts:\n\tcase %c\n", '1');
			break;
		case 'a':
			*options |= ALL;
			dbg_printf("parse_opts:\n\tcase %c\n", 'a');
			break;
		case 'A':
			*options |= ALMOSTALL;
			dbg_printf("parse_opts:\n\tcase %c\n", 'A');
			break;
		case 'h':
			*options |= HUMAN;
			dbg_printf("parse_opts:\n\tcase %c\n", 'h');
			break;
		case 'l':
			*options |= LISTING;
			dbg_printf("parse_opts:\n\tcase %c\n", 'l');
			break;
		default:
			dbg_printf("TODO: handle bad flag\n");
			fprintf(stderr, "Unknown flag\n");
			exit(2);
			break;
		}
	}
}
