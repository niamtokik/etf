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

	/* we share currently the same buffer here*/
	/* first, we encode a float */
	ei_encode_double(buffer, &index, 0.1234);

	/* next a signed long */
	ei_encode_long(buffer, &index, -1234);

	/* and finally an unsigned long */
	ei_encode_ulong(buffer, &index, 0x1234);

	/* printing buffer content (in hexadecimal) */
	ei_encoded_printf(buffer, BUFFER_SIZE);
	printf("\n");

	/* decoding part */
	int origin = 0;
	double my_double = 0;
	long my_long = 0;
	unsigned long my_ulong = 0;

	/* decode the first encoded value (double) */
	ei_decode_double(buffer, &origin, &my_double);
	printf("%f\n", my_double);

	/* decode the second encoded value (signed long) */
	ei_decode_long(buffer, &origin, &my_long);
	printf("%ld\n", my_long);

	/* decode the last encoded value (unsigned long) */
	ei_decode_ulong(buffer, &origin, &my_ulong);
	printf("0x%02lx (%lu)\n", my_ulong, my_ulong);
}
