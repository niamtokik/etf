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
atom(char *buffer, int *index, int len){
	char atom[MAXATOMLEN];
	memset(atom, 0, MAXATOMLEN);
	ei_decode_atom(buffer, index, atom);
	printf("is an atom with value '%s'", atom);
}

void
string(char *buffer, int *index, int len){
	char str[len];
	memset(str, 0, len);
	ei_decode_string(buffer, index, str);
	printf("is a string with value '%s'", str);
}

void
decode(char *buffer, int *index) {
	int mtype, msize = 0;
	ei_get_type(buffer, index, &mtype, &msize);
	switch (mtype) {
	case ERL_ATOM_EXT:
		atom(buffer, index, MAXATOMLEN);
		break;
	case ERL_STRING_EXT:
		string(buffer, index, msize);
		break;
	default:
		printf("not supported");
		ei_skip_term(buffer, index);
		break;
	}
}

void
map_key(char *buffer, int *index) {
	printf("map key ");
	decode(buffer, index);
	printf("\n");
}

void
map_value(char *buffer, int *index) {
	printf("map value ");
	decode(buffer, index);
	printf("\n");
}

int
main(void) {
	/* encoding part */
	int index = 0;
	char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);

	ei_encode_map_header(buffer, &index, 4);
	ei_encode_atom(buffer, &index, "key");
	ei_encode_string(buffer, &index, "value");
	ei_encode_atom(buffer, &index, "key2");
	ei_encode_string(buffer, &index, "value2");
	ei_encoded_printf(buffer, BUFFER_SIZE);
	printf("\n");

	/* decoding part */
	int origin = 0;
	int size = 0;
	ei_decode_map_header(buffer, &origin, &size);
	printf("map size: %d\n", size);

	int i = 0;
	for(i=0; i<size; i++) 
		if ((i%2)==0) 
			map_key(buffer, &origin);
		else
			map_value(buffer, &origin);
}
