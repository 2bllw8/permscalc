/*
 * Copyright (c) 2022 2bllw8
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include "stddef.h"
#include "stdlib.h"
#include "string.h"

#include "permscalc.h"

#define R 1 << 2
#define W 1 << 1
#define X 1 << 0

#define SYM_R 'r'
#define SYM_W 'w'
#define SYM_X 'x'
#define SYM_0 '-'
#define SYM_D 'd'
#define SYM_EXTRA_ACL '+'
#define SYM_EXTRA_EXTENDED '@'

#define LEN_NUMERIC 3
#define LEN_SYMBOLIC 9
#define LEN_SYMBOLIC_WITH_D LEN_SYMBOLIC + 1
#define LEN_SYMBOLIC_WITH_D_AND_EXTRA LEN_SYMBOLIC_WITH_D + 1

permission_t identify_type(const char *str)
{
	if (str == 0 || *str == 0) {
		return PERMISSION_TYPE_UNKNOWN;
	}

	int i = 0, len = strlen(str);

	switch (len) {
	case LEN_NUMERIC:
		while (i < len) {
			if (str[i] < '0' || str[i] > '7') {
				return PERMISSION_TYPE_UNKNOWN;
			}
			++i;
		}
		return PERMISSION_TYPE_NUMERIC;

	case LEN_SYMBOLIC:
		while (i < len) {
			if (str[i] != SYM_R && str[i] != SYM_W &&
			    str[i] != SYM_X && str[i] != SYM_0) {
				return PERMISSION_TYPE_UNKNOWN;
			}
			++i;
		}
		return PERMISSION_TYPE_SYMBOLIC;

	case LEN_SYMBOLIC_WITH_D:
		if (str[0] != SYM_0 && str[0] != SYM_D) {
			return PERMISSION_TYPE_UNKNOWN;
		}
		i = 1;
		while (i < len) {
			if (str[i] != SYM_R && str[i] != SYM_W &&
			    str[i] != SYM_X && str[i] != SYM_0) {
				return PERMISSION_TYPE_UNKNOWN;
			}
			++i;
		}
		return PERMISSION_TYPE_SYMBOLIC_WITH_D;

	case LEN_SYMBOLIC_WITH_D_AND_EXTRA:
		if ((str[0] != SYM_0 && str[0] != SYM_D) ||
		    (str[len - 1] != SYM_0 && str[len - 1] != SYM_EXTRA_ACL &&
		     str[len - 1] != SYM_EXTRA_EXTENDED)) {
			return PERMISSION_TYPE_UNKNOWN;
		}
		i = 1;
		--len;
		while (i < len) {
			if (str[i] != SYM_R && str[i] != SYM_W &&
			    str[i] != SYM_X && str[i] != SYM_0) {
				return PERMISSION_TYPE_UNKNOWN;
			}
			++i;
		}
		return PERMISSION_TYPE_SYMBOLIC_WITH_D_AND_EXTRA;
	default:
		return PERMISSION_TYPE_UNKNOWN;
	}
}

char *numeric_to_symbolic(const char *numeric)
{
	int others = numeric[2] - '0', group = numeric[1] - '0',
	    owner = numeric[0] - '0';
	char *symbolic = malloc(sizeof(char) * LEN_SYMBOLIC);
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

char *_symbolic_to_numeric(const char *symbolic, size_t len)
{
	int owner = 0, group = 0, others = 0;
	size_t i = 0;

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

	char *numeric = malloc(sizeof(char) * LEN_NUMERIC);
	numeric[0] = '0' + owner;
	numeric[1] = '0' + group;
	numeric[2] = '0' + others;
	return numeric;
}

char *symbolic_to_numeric(const char *str)
{
	return _symbolic_to_numeric(str, strlen(str));
}

char *symbolic_with_d_to_numeric(const char *str)
{
	return _symbolic_to_numeric(str + 1, strlen(str) - 1);
}

char *symbolic_with_d_and_extra_to_numeric(const char *str)
{
	return _symbolic_to_numeric(str + 1, strlen(str) - 2);
}
