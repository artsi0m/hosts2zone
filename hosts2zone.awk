#!/usr/bin/awk -f
BEGIN {
infile = "hosts";
outfile = "block.local"
while((getline blockedsite < infile) > 0 ){
    gsub("0.0.0.0 ", "", blockedsite);
# \x22 is escape sequance for double quote in ascii
    printf("local-zone: \x22%s\x22 refuse \n",\
blockedsite) > outfile;
}
close(infile);
close(outfile);
}
