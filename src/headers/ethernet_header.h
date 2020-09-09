#ifndef ETHER_H_
#define ETHER_H_

/* ethernet headers are always exactly 14 bytes */
#define SIZE_ETHERNET 14
/* Ethernet addresses are 6 bytes */
#define ETHER_ADDR_LEN	6

/* Structure of an Ethernet header */
struct ethernet_header {
        unsigned char	   ether_dhost[ETHER_ADDR_LEN]; /* destination host address */
        unsigned char  	   ether_shost[ETHER_ADDR_LEN]; /* source host address */
        unsigned short int ether_type;                	/* IP? ARP? RARP? etc */
};

void gen_ether(struct ethernet_header *ether, unsigned char shost[], unsigned char dhost[], unsigned short int type) {
	for (int i = 0; i < ETHER_ADDR_LEN; i++) {
		ether -> ether_shost[i] = shost[i];
		ether -> ether_dhost[i] = dhost[i];
	}
	ether -> ether_type = type;
}

#endif // ETHER_H_