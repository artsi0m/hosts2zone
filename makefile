all: hosts2zone gsub

hosts2zone: 
	cc hosts2zone.c -Wall -Wextra -o hosts2zone
	
gsub:
	cc gsub.c -Wall -Wextra -o gsub

fetch:
	ftp http://sbc.io/hosts/hosts

clean:
	rm hosts2zone
