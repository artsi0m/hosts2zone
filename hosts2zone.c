/*
 * Copyright (c) 2021, 2023 Artsiom Karakin <karakin2000@gmail.com>
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

#define BUFSIZ	1024

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

int
main()
{
	/* OpenBSD pledge(2) limit to stdio group of syscalls */
	if (pledge("stdio", NULL) == 1)
		err(1, "pledge");

	char *line;
	size_t spnsz;

	if ((line = calloc(sizeof(char), BUFSIZ)) == NULL)
		err(1, NULL);


	while ((fgets(line, BUFSIZ, stdin)) != NULL) {
		if (line[0] != '0' ||
		    strncmp(line, "0.0.0.0 0.0.0.0\n", BUFSIZ) == 0) {
			/* fallthrough on comment */
			;
		} else {
			/* Change LF line ending into double quote */
			line[strnlen(line, BUFSIZ) - 1] = '"';

			spnsz = strspn(line, "0.0.0.0 ");
			/*
			 * \x22 is ANSI escape sequence for double quote
			 * We need it only once, because previous was acquired
			 * when we trimmed out newline.
			 * line+spnsz is pointer to char with zeroes span'ed out
			 * by strspn.
			 */
			printf("local-zone: \x22%s refuse \n", line + spnsz);
		}
	}

}
