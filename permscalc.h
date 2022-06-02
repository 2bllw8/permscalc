/*
 * Copyright (c) 2022 2bllw8
 * SPDX-License-Identifier: GPL-3.0-only
 */

#ifndef PERMSCALC_H
#define PERMSCALC_H

typedef enum {
	PERMISSION_TYPE_UNKNOWN,
	PERMISSION_TYPE_NUMERIC,
	PERMISSION_TYPE_SYMBOLIC_WITH_D,
	PERMISSION_TYPE_SYMBOLIC,
} permission_t;

permission_t identify_type(const char *str);
char *convert_to_numeric(const char *str);
char *convert_to_symbolic(const char *numeric);
#endif
