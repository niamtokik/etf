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
fixed_list_encode(void) {
	/* encoding part */
	int index = 0;
	char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);

	/* fixed length list */
	ei_encode_list_header(buffer, &index, 3);
	ei_encode_long(buffer, &index, 1001);
	ei_encode_long(buffer, &index, 1002);
	ei_encode_long(buffer, &index, 1003);
	ei_encode_empty_list(buffer, &index);

	ei_encoded_printf(buffer, BUFFER_SIZE);
	printf("\n");

	/* decoding part */
	int origin = 0;
	int size = 0;

	/* check the list size */
	ei_decode_list_header(buffer, &origin, &size);
	printf("list size: %d\n", size);
	
	/* we assume we have only integer */
	long decoded[size];
	memset(decoded, 0, size);
	int i = 0;

	/* for each integer we store it */
	for(i=0; i<size; i++)
		ei_decode_long(buffer, &origin, &decoded[i]);

	/* we print our value */
	for(i=0; i<size; i++)
		printf("value %d: %ld\n", i, decoded[i]);
	
}

void
dynamic_list_encode(void) {
	/* encoding part */
	int index = 0;
	char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);

	/* dynamic length list */
	ei_encode_list_header(buffer, &index, 1);
	ei_encode_atom(buffer, &index, "test");
	ei_encode_list_header(buffer, &index, 1);
	ei_encode_atom(buffer, &index, "foo");
	ei_encode_empty_list(buffer, &index);

	ei_encoded_printf(buffer, BUFFER_SIZE);
	printf("\n");

	/* decoding part */
}

int
main(void) {
	printf("fixed list encoding: \n");
	fixed_list_encode();

	printf("dynamic list encoding: \n");
	dynamic_list_encode();
}
