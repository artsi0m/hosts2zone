/*
 *
 * Copyright (c) Feb, March 2021 Artsiom <karakin2000@gmail.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 * 
 */

#if defined(__FreeBSD__)
#include <sys/capsicum.h>
#endif

#include <err.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#if defined(__OpenBSD__)
#include <unistd.h>
#endif

#if defined(__FreeBSD__)
#include <capsicum_helpers.h>
#endif

int
main(){
	/* OpenBSD pledge(2) limit to stdio group of syscalls */
#if defined(__OpenBSD__)
	if (pledge("stdio", NULL) == 1)
		err(1, "pledge");
#endif

	char *line = NULL;
	size_t linesize = 0;
	ssize_t linelen;
	size_t spnsz;

#if defined(__FreeBSD__)
	cap_rights_t	rights;
#endif


	/*
	 * FreeBSD rights(4) limit to all calls given by
	 * pledge("stdio", NULL);
	 */

#if defined(__FreeBSD__)

	if (cap_enter() < 0)
		err(1, "cap_enter() failed");

	cap_rights_init(&rights,\
		CAP_FCNTL, CAP_FSTAT, CAP_FSYNC, CAP_FTRUNCATE, \
			CAP_SEEK, CAP_WRITE,);

#endif

	while ((linelen = getline(&line, &linesize, stdin)) != -1){
		if (line[0] != '0' \
	|| strncmp(line, "0.0.0.0 0.0.0.0\n", linesize) == 0 ) {
		/* fallthrough on comment */ 
				; } else {
			/* Change '\n' into '"' */
			line[strlen(line) - 1] = '"';

			spnsz = strspn(line, "0.0.0.0 ");
			/*
			 * \x22 is '"' We need only one of them, 
			 * because second '"' was acquired before
			 */
			printf("local-zone: \x22%s refuse\n",line+spnsz);
		}
	}
	
	free(line);
	if (ferror(stdin))
		err(1, "getline");
}
