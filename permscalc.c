/*
 * Copyright (c) 2022 2bllw8
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include "stdlib.h"
#include "string.h"

#include "permscalc.h"
#include <assert.h>

#define R 1 << 2
#define W 1 << 1
#define X 1 << 0

#define SYM_R 'r'
#define SYM_W 'w'
#define SYM_X 'x'
#define SYM_0 '-'
#define SYM_D 'd'

#define SYMBOLIC_LEN 9
#define SYMBOLIC_LEN_WITH_D 10
#define NUMERIC_LEN 3

permission_t identify_type(const char *str)
{
	if (str == 0 || *str == 0) {
		return PERMISSION_TYPE_UNKNOWN;
	}

	char c = *str;
	int i = 0, len = strlen(str);

	if (c == SYM_R || c == SYM_W || c == SYM_X || c == SYM_0) {
		if (len == SYMBOLIC_LEN_WITH_D) {
			if (c != SYM_0 && c != SYM_D) {
				return PERMISSION_TYPE_UNKNOWN;
			}
			i = 1;
		} else if (len != SYMBOLIC_LEN) {
			return PERMISSION_TYPE_UNKNOWN;
		}
		while (i < len) {
			c = str[i];
			if (c != SYM_R && c != SYM_W && c != SYM_X &&
			c != SYM_0) {
				return PERMISSION_TYPE_UNKNOWN;
			}
			++i;
		}
		return PERMISSION_TYPE_SYMBOLIC;
	}

	if (c >= '0' && c <= '7') {
		if (len != NUMERIC_LEN) {
			return PERMISSION_TYPE_UNKNOWN;
		}
		while (i < len) {
			c = str[i];
			if (c < '0' || c > '7') {
				return PERMISSION_TYPE_UNKNOWN;
			}
			++i;
		}
		return PERMISSION_TYPE_NUMERIC;
	}

	return PERMISSION_TYPE_UNKNOWN;
}

char *convert_to_numeric(const char *str)
{
	int owner = 0, group = 0, others = 0, i = 0, len = strlen(str);

	const char* symbolic;
	if (len == SYMBOLIC_LEN_WITH_D) {
		symbolic = str + 1;
	} else {
		symbolic = str;
	}

	while (i < len) {
		switch (symbolic[i]) {
		case SYM_R:
			switch (i) {
			case 0:
				owner |= R;
				break;
			case 3:
				group |= R;
				break;
			case 6:
				others |= R;
				break;
			}
			break;
		case SYM_W:
			switch (i) {
			case 1:
				owner |= W;
				break;
			case 4:
				group |= W;
				break;
			case 7:
				others |= W;
				break;
			}
			break;
		case SYM_X:
			switch (i) {
			case 2:
				owner |= X;
				break;
			case 5:
				group |= X;
				break;
			case 8:
				others |= X;
				break;
			}
			break;
		}
		++i;
	}

	char *numeric = malloc(sizeof(char) * NUMERIC_LEN);
	numeric[0] = '0' + owner;
	numeric[1] = '0' + group;
	numeric[2] = '0' + others;
	return numeric;
}

char *convert_to_symbolic(const char *numeric)
{
	int others = numeric[2] - '0', group = numeric[1] - '0',
	    owner = numeric[0] - '0';
	char *symbolic = malloc(sizeof(char) * SYMBOLIC_LEN);
	symbolic[0] = (owner & R) ? SYM_R : SYM_0;
	symbolic[1] = (owner & W) ? SYM_W : SYM_0;
	symbolic[2] = (owner & X) ? SYM_X : SYM_0;
	symbolic[3] = (group & R) ? SYM_R : SYM_0;
	symbolic[4] = (group & W) ? SYM_W : SYM_0;
	symbolic[5] = (group & X) ? SYM_X : SYM_0;
	symbolic[6] = (others & R) ? SYM_R : SYM_0;
	symbolic[7] = (others & W) ? SYM_W : SYM_0;
	symbolic[8] = (others & X) ? SYM_X : SYM_0;
	return symbolic;
}
