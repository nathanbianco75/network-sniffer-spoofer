//---rawtcp.c---

// Run as root or SUID 0, just datagram no data/payload

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include "../headers/ip_header.h"
#include "../headers/tcp_header.h"
#include "../headers/simple_checksum.h"

// Packet length
#define PCKT_LEN 8192
 

int main(int argc, char *argv[])
{
	int sd;

	// No data, just datagram
	char buffer[PCKT_LEN];

	// The size of the headers
	struct ip_header *ip = (struct ip_header *) buffer;
	struct tcp_header *tcp = (struct tcp_header *) (buffer + sizeof(struct ip_header));

	struct sockaddr_in sin, din;

	int one = 1;
	const int *val = &one;

	memset(buffer, 0, PCKT_LEN);


	if (argc != 5) {
		printf("- Invalid parameters!!!\n");
		printf("- Usage: %s <source hostname/IP> <source port> <target hostname/IP> <target port>\n", argv[0]);
		exit(-1);
	}


	sd = socket(PF_INET, SOCK_RAW, IPPROTO_TCP);
	if( sd < 0) {
	   perror("socket() error");
	   exit(-1);
	}
	else
		printf("socket()-SOCK_RAW and tcp protocol is OK.\n");

	// The source is redundant, may be used later if needed
	// Address family
	sin.sin_family = AF_INET;
	din.sin_family = AF_INET;

	// Source port, can be any, modify as needed
	sin.sin_port = htons(atoi(argv[2]));
	din.sin_port = htons(atoi(argv[4]));

	// Source IP, can be any, modify as needed
	sin.sin_addr.s_addr = inet_addr(argv[1]);
	din.sin_addr.s_addr = inet_addr(argv[3]);


	// IP Setup
	gen_ip(
			ip,									// ip_header to use
			// here our packet is only ip + tcp headers, w/ no payload
			// so packet length is simply length of headers added
			sizeof(struct ip_header)
				+ sizeof(struct tcp_header),	// iph_len = packet length
			6,									// ip protocol, 6 = TCP
			csum((unsigned short *) buffer,
			(sizeof(struct ip_header)
				+ sizeof(struct tcp_header))),	// checksum, using simple_checksum
			argv[1],							// source/sender ip
			argv[3]								// destination/receiver ip
			);

	// TCP Setup
	gen_tcp(
			tcp,					// tcp_header to use
			htons(atoi(argv[2])),	// source/sender port
			htons(atoi(argv[4])),	// destination/receiver port
			0						// checksum, 0 = Done by kernel
			);

	 
	// Inform the kernel do not fill up the headers' structure, we fabricated our own
	if (setsockopt(sd, IPPROTO_IP, IP_HDRINCL, val, sizeof(one)) < 0) {
		perror("setsockopt() error");
		exit(-1);
	}
	else
	   printf("setsockopt() is OK\n");


	printf("Using:::::Source IP: %s port: %u, Target IP: %s port: %u.\n", argv[1], atoi(argv[2]), argv[3], atoi(argv[4]));

	 
	// sendto() loop, send every 2 second for 50 counts
	unsigned int count;
	for (count = 0; count < 20; count++) {
		if (sendto(sd, buffer, ip->iph_len, 0, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
			// Verify
		   perror("sendto() error");
		   exit(-1);
		}
		else
		   printf("Count #%u - sendto() is OK\n", count);
		
		sleep(2);
	}

	close(sd);
	return 0;
}

 
/* TERMINAL EXAMPLE
[root@bakawali testraw]# sudo ./rawtcp

- Invalid parameters!!!

- Usage: ./rawtcp <source hostname/IP> <source port> <target hostname/IP> <target port>

[root@bakawali testraw]# sudo ./rawtcp 10.10.10.100 23 203.106.93.88 8008

socket()-SOCK_RAW and tcp protocol is OK.

setsockopt() is OK

Using:::::Source IP: 10.10.10.100 port: 23, Target IP: 203.106.93.88 port: 8008.

Count #0 - sendto() is OK

Count #1 - sendto() is OK

Count #2 - sendto() is OK

Count #3 - sendto() is OK

Count #4 - sendto() is OK

...
*/