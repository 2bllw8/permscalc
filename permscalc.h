/*
 * Copyright (c) 2022 2bllw8
 * SPDX-License-Identifier: GPL-3.0-only
 */

#ifndef PERMSCALC_H
#define PERMSCALC_H

typedef enum {
	PERMISSION_TYPE_UNKNOWN,
	PERMISSION_TYPE_NUMERIC,
	PERMISSION_TYPE_SYMBOLIC,
	PERMISSION_TYPE_SYMBOLIC_WITH_PREFIX,
	PERMISSION_TYPE_SYMBOLIC_WITH_PREFIX_AND_POSTFIX,
} permission_t;

permission_t identify_type(const char *str);
char *symbolic_to_numeric(const char *str);
char *symbolic_with_prefix_to_numeric(const char *str);
char *symbolic_with_prefix_and_postfix_to_numeric(const char *str);
char *numeric_to_symbolic(const char *numeric);
#endif
