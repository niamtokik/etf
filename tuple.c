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

int
main(void) {
	/* encoding part */
	int index = 0;
	char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);

	/* encode a tuple of arity 3 */
	ei_encode_tuple_header(buffer, &index, 3);

	/* next store 3 atoms in this tuple */
	ei_encode_atom(buffer, &index, "test1");
	ei_encode_atom(buffer, &index, "test2");
	ei_encode_atom(buffer, &index, "test3");
	ei_encoded_printf(buffer, BUFFER_SIZE);
	printf("\n");

	/* decoding part */
	int origin = 0;
	int data_type, data_size = 0;

	/* what is the first encoded value? */
	ei_get_type(buffer, &origin, &data_type, &data_size);

	/* if its a tuple... */
	if (data_type == ERL_SMALL_TUPLE_EXT ||
	    data_type == ERL_LARGE_TUPLE_EXT) {

		/* ... we decode it. */
		ei_decode_tuple_header(buffer, &origin, &data_size);
		printf("size: %d\n", data_size);

		/* foreach value stored in this tuple */
		int i = 0;
		for(i=0; i<data_size; i++) {
			char my_atom[MAXATOMLEN];
			memset(my_atom, 0, MAXATOMLEN);
			ei_decode_atom(buffer, &origin, my_atom);
			printf("item %d: %s\n", i, my_atom);
		}
	}
}
