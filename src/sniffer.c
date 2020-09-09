#include <pcap.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include "headers/ethernet_header.h"
#include "headers/icmp_header.h"
#include "headers/ip_header.h"
#include "headers/simple_checksum.h"
#include "headers/tcp_header.h"
#include "headers/udp_header.h"
#include "headers/util_sniff.h"

/*
 * print help text
 */
void print_app_usage(void) {
	printf("Usage: sudo ./sniffer [filter] [interface]\n");
	printf("\n");
	printf("Options:\n");
	printf("    filter       Sniff packet type <filter>.\n");
	printf("    interface    Listen on <interface> for packets.\n");
	printf("\n");
}


int main(int argc, char *argv[])
{
	char  *filter_exp = new char[]("");		/* filter expression */
	char *dev = NULL;
	if (argc == 2) {
		filter_exp = argv[1];
	}
	else if (argc == 3) {
		dev = argv[2];
	}
	else if (argc > 3) {
		fprintf(stderr, "error: unrecognized command-line options\n\n");
		print_app_usage();
		exit(EXIT_FAILURE);
	}
	sniff(filter_exp, dev);
	return 0;
}
