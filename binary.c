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

	/* setting our binary data */
	char binary_term[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0,
		                 'a', 'b', 'c', 'd', 'e', 'f' };

	/* encode it in buffer */
	ei_encode_binary(buffer, &index, binary_term, 16);

	/* print buffer content */
	ei_encoded_printf(buffer, BUFFER_SIZE);
	printf("\n");

	/* decoding part */
	int origin = 0;
	int data_type = 0;
	int data_size = 0;

	/* get type and size */
	ei_get_type(buffer, &origin, &data_type, &data_size);

	/* if data-structure is binary */
	if (data_type == ERL_BINARY_EXT) {
		/* allocate a buffer on stack of size of the binary */
		char binary[data_size];

		/* convert data_size to long */
		long binary_len = (long)data_size;

		/* decode our encoded buffer in our decoded buffer */
		ei_decode_binary(buffer, &origin, binary, &binary_len);

		/* print all decoded value */
		int i=0;
		for(i=0; i<data_size; i++)
			printf("value: %d \n", binary[i]);
	}
}
