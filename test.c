/*
 * Copyright (c) 2022 2bllw8
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include "assert.h"
#include "string.h"

#include "permscalc.h"

int main(int argc, char **argv)
{
	assert(strcmp("777", convert_to_numeric("rwxrwxrwx")) == 0);
	assert(strcmp("000", convert_to_numeric("---------")) == 0);
	assert(strcmp("444", convert_to_numeric("r--r--r--")) == 0);
	assert(strcmp("222", convert_to_numeric("-w--w--w-")) == 0);
	assert(strcmp("111", convert_to_numeric("--x--x--x")) == 0);
	assert(strcmp("653", convert_to_numeric("rw-r-x-wx")) == 0);

	assert(strcmp("644", convert_to_numeric("-rw-r--r--")) == 0);
	assert(strcmp("644", convert_to_numeric("drw-r--r--")) == 0);

	assert(strcmp("rwxrwxrwx", convert_to_symbolic("777")) == 0);
	assert(strcmp("---------", convert_to_symbolic("000")) == 0);
	assert(strcmp("r--r--r--", convert_to_symbolic("444")) == 0);
	assert(strcmp("-w--w--w-", convert_to_symbolic("222")) == 0);
	assert(strcmp("--x--x--x", convert_to_symbolic("111")) == 0);
	assert(strcmp("rw-r-x-wx", convert_to_symbolic("653")) == 0);

	assert(strcmp("rw-r-x-wx", convert_to_symbolic(convert_to_numeric(
					   "rw-r-x-wx"))) == 0);
	assert(strcmp("---------", convert_to_symbolic(convert_to_numeric(
					   "---------"))) == 0);
	assert(strcmp("r--r--r--", convert_to_symbolic(convert_to_numeric(
					   "r--r--r--"))) == 0);
	assert(strcmp("-w--w--w-", convert_to_symbolic(convert_to_numeric(
					   "-w--w--w-"))) == 0);
	assert(strcmp("--x--x--x", convert_to_symbolic(convert_to_numeric(
					   "--x--x--x"))) == 0);
	assert(strcmp("rw-r-x-wx", convert_to_symbolic(convert_to_numeric(
					   "rw-r-x-wx"))) == 0);

	assert(strcmp("777", convert_to_numeric(convert_to_symbolic("777"))) ==
	       0);
	assert(strcmp("000", convert_to_numeric(convert_to_symbolic("000"))) ==
	       0);
	assert(strcmp("444", convert_to_numeric(convert_to_symbolic("444"))) ==
	       0);
	assert(strcmp("222", convert_to_numeric(convert_to_symbolic("222"))) ==
	       0);
	assert(strcmp("111", convert_to_numeric(convert_to_symbolic("111"))) ==
	       0);
	assert(strcmp("653", convert_to_numeric(convert_to_symbolic("653"))) ==
	       0);
}
