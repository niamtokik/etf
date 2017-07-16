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
	ei_x_buff buffer;
	ei_x_new_with_version(&buffer);
	ei_x_encode_list_header(&buffer, 1);
	ei_x_encode_tuple_header(&buffer, 2);
	ei_x_encode_atom(&buffer, "jid");
	ei_x_encode_long(&buffer, 9999);
	ei_x_encode_empty_list(&buffer);
	ei_encoded_printf(buffer.buff, buffer.buffsz/8);
	printf("\n");

	/* decoding part */
	char *buff = buffer.buff;
	int index = 0;
	int version = 0;
	char my_key[MAXATOMLEN];
	long my_value = 0;

	ei_decode_version(buff, &index, &version);
	int list_arity = 0;
	ei_decode_list_header(buff, &index, &list_arity);

	int tuple_arity = 0;
	ei_decode_tuple_header(buff, &index, &tuple_arity);
	ei_decode_atom(buff, &index, my_key);
	ei_decode_long(buff, &index, &my_value);

	printf("decoded: [{%s,%ld}]\n", my_key, my_value);

	ei_x_free(&buffer);
}
