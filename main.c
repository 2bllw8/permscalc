/*
 * Copyright (c) 2022 2bllw8
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include "stdio.h"
#include "permscalc.h"

int parse(const char *input)
{
	switch (identify_type(input)) {
	case PERMISSION_TYPE_NUMERIC:
		fprintf(stdout, "%s\n", convert_to_symbolic(input));
		break;
	case PERMISSION_TYPE_SYMBOLIC:
		fprintf(stdout, "%s\n", convert_to_numeric(input));
		break;
	case PERMISSION_TYPE_UNKNOWN:
	default:
		fprintf(stderr, "%s: invalid permissions value\n", input);
		return 0;
	}
	return 1;
}

int main(int argc, char **argv)
{
	if (argc == 1) {
		char *line = 0;
		size_t len = 0, line_len = 0;
		while ((line_len = getline(&line, &len, stdin)) != -1) {
			line[line_len - 1] = 0;
			if (!parse((const char*) line)) {
				return 1;
			}
		}

	} else {
		int i = 1;
		while (i < argc) {
			if (!parse((const char *) argv[i++])) {
				return 1;
			}
		}
	}

	return 0;
}
