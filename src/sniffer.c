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
	printf("Usage: %s [interface]\n", APP_NAME);
	printf("\n");
	printf("Options:\n");
	printf("    interface    Listen on <interface> for packets.\n");
	printf("\n");
}


int main(int argc, char **argv)
{
	if (argc == 2) {
		dev = argv[1];
	}
	else if (argc > 2) {
		fprintf(stderr, "error: unrecognized command-line options\n\n");
		print_app_usage();
		exit(EXIT_FAILURE);
	}
	sniff(argc, argv);
	return 0;
}
