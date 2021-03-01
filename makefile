all: hosts2zone

hosts2zone: 
	cc -D"__OpenBSD__" hosts2zone.c -Wall -Wextra -o hosts2zone

fetch:
	ftp http://sbc.io/hosts/hosts

clean:
	rm hosts2zone hosts hosts2zone.core
