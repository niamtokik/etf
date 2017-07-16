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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ei.h>
#include <unistd.h>
#define BUFFER_SIZE 1024

void ei_encoded_printf(char *, size_t);
void ei_encoded_fprinf(FILE *, char *, size_t);
void ei_raw_print(char *, size_t);

void
ei_encoded_printf(char *buffer, size_t s) {
	int i = 0;
	for(i=0; i<s; i++) 
		printf("%02x", buffer[i]);
}

void
ei_encoded_fprintf(FILE *fd, char *buffer, size_t s) {
	int i = 0;
	for(i=0; i<s; i++)
		fprintf(fd, "%02x", buffer[i]); 
}

void
ei_raw_print(char *buffer, size_t s) {
	int i = 0;
	for(i=0; i<s; i++)
		write(1, &buffer[i], sizeof(char));
}

void
ei_x_vsize_fprintf(FILE *fd, ei_x_buff *buffer, int s) {
	char *c = (char *) &buffer->buffsz;
	s--;
	for(;s>=0; s--)
		fprintf(fd, "%c", *(c+s));
}

void
ei_x_size8_fprintf(FILE *fd, ei_x_buff *buffer) {
	char *c = (char *) &buffer->buffsz;
	fprintf(fd, "%c", *c);
}

void
ei_x_size16_fprintf(FILE *fd, ei_x_buff *buffer) {
	char *c = (char *) &buffer->buffsz;
	fprintf(fd, "%c%c", *(c+1), *c);
}

void
ei_x_size32_fprintf(FILE *fd, ei_x_buff *buffer) {
	fprintf(fd,"%c%c%c%c" 
		,(char)(buffer->buffsz>>24) 
		,(char)(buffer->buffsz>>16) 
		,(char)(buffer->buffsz>>8)
		,(char)(buffer->buffsz)); 
}

void
ei_x_size32_write(int fd, ei_x_buff *buffer) {
	write(fd, (char *) &buffer->buffsz, 4);
}

void
ei_x_fprintf_raw(FILE *fd, ei_x_buff *buffer) {
  int i=0;
  for(i=0; i<(buffer->buffsz); i++)
	fprintf(fd, "%c", buffer->buff[i]);
}

void
ei_x_write(int fd, ei_x_buff *buffer) {
	write(fd, buffer->buff, buffer->buffsz);
}
