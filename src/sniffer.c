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

int main(int argc, char **argv)
{
	void sniff(argc, argv);
	return 0;
}
