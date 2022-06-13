/*
 * Copyright (c) 2022 2bllw8
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include "assert.h"
#include "stddef.h"
#include "stdlib.h"
#include "string.h"

#include "permscalc.h"

int main(int argc, char **argv)
{
	assert(strcmp("777", symbolic_to_numeric("rwxrwxrwx")) == 0);
	assert(strcmp("000", symbolic_to_numeric("---------")) == 0);
	assert(strcmp("444", symbolic_to_numeric("r--r--r--")) == 0);
	assert(strcmp("222", symbolic_to_numeric("-w--w--w-")) == 0);
	assert(strcmp("111", symbolic_to_numeric("--x--x--x")) == 0);
	assert(strcmp("653", symbolic_to_numeric("rw-r-x-wx")) == 0);

	assert(strcmp("644", symbolic_with_d_to_numeric("-rw-r--r--")) == 0);
	assert(strcmp("644", symbolic_with_d_to_numeric("drw-r--r--")) == 0);

	assert(strcmp("644", symbolic_with_d_and_extra_to_numeric(
				     "-rw-r--r--@")) == 0);
	assert(strcmp("761", symbolic_with_d_and_extra_to_numeric(
				     "drwxrw---x@")) == 0);
	assert(strcmp("123", symbolic_with_d_and_extra_to_numeric(
				     "---x-w--wx+")) == 0);

	assert(strcmp("rwxrwxrwx", numeric_to_symbolic("777")) == 0);
	assert(strcmp("---------", numeric_to_symbolic("000")) == 0);
	assert(strcmp("r--r--r--", numeric_to_symbolic("444")) == 0);
	assert(strcmp("-w--w--w-", numeric_to_symbolic("222")) == 0);
	assert(strcmp("--x--x--x", numeric_to_symbolic("111")) == 0);
	assert(strcmp("rw-r-x-wx", numeric_to_symbolic("653")) == 0);

	assert(strcmp("rw-r-x-wx", numeric_to_symbolic(symbolic_to_numeric(
					   "rw-r-x-wx"))) == 0);
	assert(strcmp("---------", numeric_to_symbolic(symbolic_to_numeric(
					   "---------"))) == 0);
	assert(strcmp("r--r--r--", numeric_to_symbolic(symbolic_to_numeric(
					   "r--r--r--"))) == 0);
	assert(strcmp("-w--w--w-", numeric_to_symbolic(symbolic_to_numeric(
					   "-w--w--w-"))) == 0);
	assert(strcmp("--x--x--x", numeric_to_symbolic(symbolic_to_numeric(
					   "--x--x--x"))) == 0);
	assert(strcmp("rw-r-x-wx", numeric_to_symbolic(symbolic_to_numeric(
					   "rw-r-x-wx"))) == 0);

	assert(strcmp("777", symbolic_to_numeric(numeric_to_symbolic("777"))) ==
	       0);
	assert(strcmp("000", symbolic_to_numeric(numeric_to_symbolic("000"))) ==
	       0);
	assert(strcmp("444", symbolic_to_numeric(numeric_to_symbolic("444"))) ==
	       0);
	assert(strcmp("222", symbolic_to_numeric(numeric_to_symbolic("222"))) ==
	       0);
	assert(strcmp("111", symbolic_to_numeric(numeric_to_symbolic("111"))) ==
	       0);
	assert(strcmp("653", symbolic_to_numeric(numeric_to_symbolic("653"))) ==
	       0);
}
