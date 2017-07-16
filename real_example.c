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
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include "etf.h"
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

#define PROCFS_PATH	"/proc"
#define LIMIT_NS	256
#define G(X)		# X
#define GLUE(X,Y) 	X ## Y

/* This macro template will generate read_ns_* functions 
 * You can generate all needed ns record (will return long type)
 */
#define READ_NS(X) 						\
	long GLUE(read_ns_,X)(long pid, size_t len) {		\
	char path[len+1];					\
	memset(path, 0, len+1);					\
	snprintf(path, len+1, PROCFS_PATH "/%ld/ns/" G(X), pid);\
	return read_symlink_namespace(path, len+1); }

/* This macro template will generate encode_ns_* functions
 * used to encode namespace in ETF
 */
#define ENCODE_NS(X) 						\
	void GLUE(encode_ns_,X)(ei_x_buff *buffer, long pid) { 	\
	ei_x_encode_list_header(buffer, 1);			\
	ei_x_encode_tuple_header(buffer, 2);			\
	ei_x_encode_atom(buffer, G(X));				\
	ei_x_encode_long(buffer, 				\
		GLUE(read_ns_,X)(pid, LIMIT_NS)); }

/* This macro generate read_ns_* and encode_ns_* functions
 */
#define NS(X) 		\
	READ_NS(X); 	\
	ENCODE_NS(X)

/* This macro generate read_ns_* and encode_ns_* functions
 * prototypes
 */
#define NS_PROTOTYPE(X) \
	void GLUE(encode_ns,X)(ei_x_buff *, long); \
	long GLUE(read_ns_,X)(long, size_t);

/* Defining functions prototypes
 * Those functions will be available in all our code
 */
int is_digit(char);
long get_namespace(char *, size_t);
int string_is_number(char *, size_t);
long read_symlink_namespace(const char *, size_t);
void print_pids(FILE *, ei_x_buff *);
void list_pids(FILE *, const char *);
NS_PROTOTYPE(cgroup);
NS_PROTOTYPE(ipc);
NS_PROTOTYPE(mnt);
NS_PROTOTYPE(net);
NS_PROTOTYPE(pid);
NS_PROTOTYPE(user);
NS_PROTOTYPE(uts);

/* All our file-descriptor are defined
 * as global variables 
 */
FILE *out, *in, *err;

int
is_digit(char c) {
  if (c>='0' && c<='9') 
    return 1;
  return 0;
}

long
get_namespace(char *value,
	      size_t size) {
  int i = 0;
  int b = 0;
  char buffer[size+1];
  memset(buffer, 0, size+1);
  if (value[i]=='-') {
    buffer[b] = '-';
    b += 1;
  }
  for(i=1; value[i]!=0 && i<size; i++) {
    if (is_digit(value[i])) {
      buffer[b] = value[i];
      b += 1;
    }
  }
  return strtol(buffer, 0, 10);
}

int
string_is_number(char *string, 
	         size_t size) {
  int i = 0;
  for(i=0; string[i]!=0 && i<size; i++)
    if (!is_digit(string[i]))
      return 0;
  return 1;
}

long
read_symlink_namespace(const char *symlink_path,
	               size_t name_len) {
  char buffer[name_len+1];
  memset(buffer, 0, name_len+1);
  ssize_t size;
  if((size=readlink(symlink_path, buffer, name_len))<0) {
    return -1;
  }
  else {
    long i = get_namespace(buffer, size);
    return i;
  }
}

NS(cgroup);
NS(ipc);
NS(mnt);
NS(net);
NS(pid);
NS(user);
NS(uts);

void
encode_pid(ei_x_buff *buffer,
	   long pid) {
   /* a pid struct is contained in list */
   ei_x_encode_list_header(buffer, 1);

   /* and is defined by a tuple of arity 2*/
   ei_x_encode_tuple_header(buffer, 2);

   /* the first element is the pid itself */
   ei_x_encode_long(buffer, pid); 

   /* and the rest is list of namespaces */
   encode_ns_cgroup(buffer, pid);
   encode_ns_ipc(buffer,pid);
   encode_ns_mnt(buffer,pid);
   encode_ns_net(buffer,pid);
   encode_ns_pid(buffer,pid);
   encode_ns_user(buffer,pid);
   encode_ns_uts(buffer,pid);

   /* finalize namespaces list here */
   ei_x_encode_empty_list(buffer);
}

void
print_pids(FILE *fd,
	   ei_x_buff *buffer) {
  /* protocol used by Erlang port 
   * first 32bits (4bytes) defined size of
   * the binary pattern
   **/
  ei_x_size32_fprintf(fd, buffer);

  /* we can now print the content of 
   * our buffer
   */
  ei_x_fprintf_raw(fd, buffer);
}

void
list_pids(FILE *out,
	  const char *path) {
  /* initialize our dynamic buffer*/
  ei_x_buff buffer;
  ei_x_new_with_version(&buffer);

  /* initialize our directory file-descriptor */
  struct dirent *dir;
  DIR *fdir = opendir(path);

  while((dir=readdir(fdir))!=NULL)
    /* If directory is an integer, its a pid... */
    if (string_is_number(dir->d_name, 256))
      /* we can encode its content. */
      encode_pid(&buffer, strtol(dir->d_name, 0, 10));

  /* last term is an empty list (make our full list) */
  ei_x_encode_empty_list(&buffer);

  /* We print our data to standard output */
  print_pids(out, &buffer);

  /* close directory and free our buffer */
  closedir(fdir);
  ei_x_free(&buffer);
}

int
main(void) {
  /* initialize file-descriptor 
   * 'in' is stdin set to read-only
   * 'out' is stdout set to write-only
   */
  in = fdopen(0, "r");
  out = fdopen(1, "w");
  err = fdopen(2, "w");

  /* fread variables used to catch input */
  ssize_t s;
  char c[1];

  /* we want to read from standard input until
   * the end of the stream (EOF)... 
   */
  while((s=fread(c, sizeof(char), 1, in)) != 0) {

    /* ... and if we get 'l' string, we print pids */
    if (c[0]=='l')
      list_pids(out, PROCFS_PATH);
  }

  /* we don't need those file-descriptor anymore */
  fclose(err);
  fclose(out);
  fclose(in);
}
