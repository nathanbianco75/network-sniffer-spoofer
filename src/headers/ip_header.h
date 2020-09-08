#ifndef IP_H_
#define IP_H_

/* Structure of an IP header */
struct ip_header {
	unsigned char      iph_ihl:5, /* Little-endian */
					   iph_ver:4;
	unsigned char      iph_tos;
	unsigned short int iph_len;
	unsigned short int iph_ident;
	unsigned char      iph_flags;
	unsigned short int iph_offset;
	unsigned char      iph_ttl;
	unsigned char      iph_protocol;
	unsigned short int iph_chksum;
	unsigned int       iph_sourceip;
	unsigned int       iph_destip;
};

void gen_ip(struct ip_header *ip, unsigned short int len, unsigned char protocol, unsigned short int chksum, unsigned int sourceip, unsigned int destip) {
	ip -> iph_ihl = 5;
	ip -> iph_ver = 4;
	ip -> iph_tos = 16;
	ip -> iph_len = len;
	ip -> iph_ident = htons(54321);
	ip -> iph_offset = 0;
	ip -> iph_ttl = 64;
	ip -> iph_protocol = protocol;
	//ip -> iph_chksum = 0; // Done by kernel
	ip -> iph_chksum = chksum;
	ip -> iph_sourceip = sourceip;
	ip -> iph_destip = destip;
}

#endif // IP_H_