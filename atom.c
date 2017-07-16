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
	FILE *fd = fdopen(1, "w");

	/* encoding part*/
	int index = 0;	// buffer index initialization
	char buffer[BUFFER_SIZE]; // buffer allocated on stack
	memset(buffer, 0, BUFFER_SIZE); // sanitize buffer

	/* see MAXATOMLEN macro, size limited to 255 */
	ei_encode_atom(buffer, &index, "test");
	fprintf(fd, "encoded value: ");
	ei_encoded_fprintf(fd, buffer, BUFFER_SIZE);
	fprintf(fd, "\n");

	/* decoding part*/
	int origin = 0;
	char my_atom[MAXATOMLEN];
	memset(my_atom, 0, MAXATOMLEN);
	
	ei_decode_atom(buffer, &origin, my_atom);
	fprintf(fd, "decoded value: %s\n", my_atom);

	fclose(fd);
}
