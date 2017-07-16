/*
 * Copyright (c) 2017, Mathieu Kerjouan <contact@steepath.eu>
 * 
 * Permission to use,  copy, modify, and distribute  this software for
 * any purpose  with or without  fee is hereby granted,  provided that
 * the above copyright notice and this permission notice appear in all
 * copies.
 * 
 * THE  SOFTWARE IS  PROVIDED "AS  IS"  AND THE  AUTHOR DISCLAIMS  ALL
 * WARRANTIES  WITH  REGARD TO  THIS  SOFTWARE  INCLUDING ALL  IMPLIED
 * WARRANTIES OF  MERCHANTABILITY AND FITNESS.  IN NO EVENT  SHALL THE
 * AUTHOR   BE  LIABLE   FOR   ANY  SPECIAL,   DIRECT,  INDIRECT,   OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF  USE,  DATA  OR  PROFITS,  WHETHER IN  AN  ACTION  OF  CONTRACT,
 * NEGLIGENCE  OR  OTHER  TORTIOUS  ACTION,   ARISING  OUT  OF  OR  IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 * 
 */

#include "etf.h"

void
type(char *buffer, int *index){
	int data_type, data_size = 0;
	ei_get_type(buffer, index, &data_type, &data_size);
	switch(data_type) {
		case ERL_SMALL_INTEGER_EXT:
			printf("small integer\n");
			break;
		case ERL_INTEGER_EXT:
			printf("integer\n");
			break;
		case ERL_FLOAT_EXT:
			printf("float\n");
			break;
		case NEW_FLOAT_EXT:
			printf("new float\n");
			break;
		case ERL_ATOM_EXT:
			printf("atom\n");
			break;
		case ERL_SMALL_ATOM_EXT:
			printf("small atom\n");
			break;
		case ERL_ATOM_UTF8_EXT:
			printf("utf8 atom\n");
			break;
		case ERL_SMALL_ATOM_UTF8_EXT:
			printf("small utf8 atom\n");
			break;
		case ERL_REFERENCE_EXT:
			printf("reference\n");
			break;
		case ERL_NEW_REFERENCE_EXT:
			printf("new reference\n");
			break;
		case ERL_NEWER_REFERENCE_EXT:
			printf("newer reference\n");
			break;
		case ERL_PORT_EXT:
			printf("port\n");
			break;
		case ERL_NEW_PORT_EXT:
			printf("new port\n");
			break;
		case ERL_PID_EXT:
			printf("pid\n");
			break;
		case ERL_NEW_PID_EXT:
			printf("new pid\n");
			break;
		case ERL_SMALL_TUPLE_EXT:
			printf("small tuple (%d)\n", data_size);
			break;
		case ERL_LARGE_TUPLE_EXT:
			printf("large tuple (%d)\n", data_size);
			break;
		case ERL_NIL_EXT:
			printf("nil\n");
			break;
		case ERL_STRING_EXT:
			printf("string (%d)\n", data_size);
			break;
		case ERL_LIST_EXT:
			printf("list (%d)\n", data_size);
			break;
		case ERL_BINARY_EXT:
			printf("binary (%d)\n", data_size);
			break;
		case ERL_SMALL_BIG_EXT:
			printf("small bignum\n");
			break;
		case ERL_LARGE_BIG_EXT:
			printf("large bignum\n");
			break;
		case ERL_NEW_FUN_EXT:
			printf("new fun\n");
			break;
		case ERL_MAP_EXT:
			printf("map (%d)\n", data_size);
			break;
		case ERL_FUN_EXT:
			printf("fun\n");
			break;
		default:
			printf("unsupported\n");
	}
}


int
main(void) {
	int index = 0;
	char buffer[1] = { 'b' };
	type(buffer, &index);
}
