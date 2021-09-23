all: hosts2zone gsub

gsub:
	cc gsub.c -Wall -Wextra -o gsub

hosts2zone: 
	cc hosts2zone.c -Wall -Wextra -o hosts2zone

fetch:
	ftp http://sbc.io/hosts/hosts

clean:
	rm hosts2zone hosts
