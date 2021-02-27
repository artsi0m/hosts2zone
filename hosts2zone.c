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
