all: hosts2zone

hosts2zone: 
	cc hosts2zone.c -Wall -Wextra -o hosts2zone

fetch:
	ftp http://sbc.io/hosts/hosts

tests: fetch

clean:
	rm hosts2zone hosts
