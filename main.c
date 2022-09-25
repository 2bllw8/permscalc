/*
 * Copyright (c) 2022 2bllw8
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include "permscalc.h"

#include <getopt.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int parse(const char *input)
{
	char *output;
	switch (identify_type(input)) {
	case PERMISSION_TYPE_NUMERIC:
		output = numeric_to_symbolic(input);
		break;
	case PERMISSION_TYPE_SYMBOLIC:
		output = symbolic_to_numeric(input);
		break;
	case PERMISSION_TYPE_SYMBOLIC_WITH_PREFIX:
		output = symbolic_with_prefix_to_numeric(input);
		break;
	case PERMISSION_TYPE_SYMBOLIC_WITH_PREFIX_AND_POSTFIX:
		output = symbolic_with_prefix_and_postfix_to_numeric(input);
		break;
	case PERMISSION_TYPE_UNKNOWN:
	default:
		fprintf(stderr, "%s: invalid permissions value\n", input);
		return 0;
	}
	fprintf(stdout, "%s\n", output);
	free(output);
	return 1;
}

int parse_path(const char *path)
{
	struct stat path_stat;
	if (stat(path, &path_stat) < 0) {
		return 0;
	}

	int owner = (path_stat.st_mode & S_IRUSR ? 4 : 0) |
		    (path_stat.st_mode & S_IWUSR ? 2 : 0) |
		    (path_stat.st_mode & S_IXUSR ? 1 : 0);
	int group = (path_stat.st_mode & S_IRGRP ? 4 : 0) |
		    (path_stat.st_mode & S_IWGRP ? 2 : 0) |
		    (path_stat.st_mode & S_IXGRP ? 1 : 0);
	int other = (path_stat.st_mode & S_IROTH ? 4 : 0) |
		    (path_stat.st_mode & S_IWOTH ? 2 : 0) |
		    (path_stat.st_mode & S_IXOTH ? 1 : 0);

	char numeric[] = {
		owner + '0',
		group + '0',
		other + '0',
	};

	printf("%s\n", numeric);
	return 1;
}

int interactive_mode()
{
	char *line = 0;
	size_t len = 0, line_len = 0;
	while ((line_len = getline(&line, &len, stdin)) != -1) {
		line[line_len - 1] = 0;
		if (!parse((const char *)line)) {
			return 0;
		}
	}
	return 1;
}

int main(int argc, char **argv)
{
	if (argc == 1) {
		return interactive_mode() == 1;
	}

	static struct option options[] = {
		{ "file", required_argument, 0, 'f' },
	};

	int index;
	int opt;
	while ((opt = getopt_long(argc, argv, "f:c:", options, &index)) != -1) {
		switch (opt) {
		case 'f':
			if (!parse_path(optarg)) {
				return 1;
			}
			break;
		}
	}
	while (optind < argc) {
		parse(argv[optind++]);
	}

	return 0;
}
