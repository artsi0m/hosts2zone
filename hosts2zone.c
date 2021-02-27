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

#include <err.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int
main(){

	if (pledge("stdio", NULL) == 1)
		err(1, "pledge");

	char *line = NULL;
	size_t linesize = 0;
	ssize_t linelen;

	char *pch;

	while ((linelen = getline(&line, &linesize, stdin)) != -1){
		if (line[0] != '0' \
	|| strncmp(line, "0.0.0.0 0.0.0.0\n", linesize) == 0 ) {
		/* fallthrough on comment */ 
				; } else {

			pch = strstr(line, "0.0.0.0 ");
			if (pch != NULL)
				/* 8 is number of chars in substring */
				strncpy(pch, "", 8);

			fwrite(line, linelen, 1, stdout);
		}
	}
	
	free(line);
	if (ferror(stdin))
		err(1, "getline");
}
