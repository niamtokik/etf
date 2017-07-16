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
	int index = 0;			// buffer index
	char buffer[BUFFER_SIZE];	// buffer on allocated on stack
	memset(buffer, 0, BUFFER_SIZE);	// sanatize buffer

	/* encode current ETF version in buffer */
	ei_encode_version(buffer, &index);
	
	/* print encoded value */
	ei_encoded_printf(buffer, BUFFER_SIZE);
	printf("\n");
	
	/* decoded part */
	int origin = 0;		// origin index (0)
	int version = 0;	// version container (integer)

	/* decode first term from buffer into version variable */
	ei_decode_version(buffer, &origin, &version);

	/* print version in decimal format */
	printf("version: %d\n", version);
}
