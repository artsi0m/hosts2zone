hosts2zone: hosts2zone.c

dist: hosts2zone.c
	cc hosts2zone.c -Wall -Wextra -Werror -o hosts2zone

debug: hosts2zone.c
	cc hosts2zone.c -O0 -Wall -Wextra -g -o hosts2zone
