#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "Show.h"
#include "Scan.h"

/*
FULL is all tcp and udp ports scan
FULLTCP is all tcp ports scan
FULLUDP is all udp ports scan
NORMAL is all wellknown tcp and udp ports scan
ARP_DISCOVER is a network discover using arp packets
PING_DISCOVER is a network discover using ping
*/

typedef enum { FULL, FULLTCP, FULLUDP, NORMAL, ARP_DISCOVER, PING_DISCOVER } scan_type;

int main(int argc, char *argv[]) {
	
	scan_type scan;
	int scan_index = 0;
	int address_index = 0;
	int netmask_index = 0;
	bool help = false;
	bool verbose = false;

	/* Parsing arguments */
	for (int index = 1; index < argc && argv[index][0] == '-'; index++) {
		if ((!strcmp(argv[index], "-s")) || (!strcmp(argv[index], "--scan-type"))) {
      			scan_index = index;	
			break;
		} else if ((!strcmp(argv[index], "-a")) || (!strcmp(argv[index], "--address"))) {
			address_index = index;
			break;
		} else if ((!strcmp(argv[index], "-n")) || (!strcmp(argv[index], "--netmask"))) {
			int netmask_index = index;
			break;
		} else if ((!strcmp(argv[index], "-h")) || (!strcmp(argv[index], "--help"))) {
			help = true;
			break;
		} else if ((!strcmp(argv[index], "-v")) || (!strcmp(argv[index], "--verbose"))) {
			verbose = true;
			break;
		}
		
	}

	if (help) showHelp();

	if (scan_index == 0) {
		if (verbose) printf("Scan-type option not set, assuming a normal scan");
		scan = NORMAL;
	} else {
		if ((!strcmp(argv[index+1]) || 
		
