#ifndef TCP_H_
#define TCP_H_

/* Structure of a TCP header */
struct tcp_header {
	unsigned short int tcph_srcport;
	unsigned short int tcph_destport;
	unsigned int       tcph_seqnum;
	unsigned int       tcph_acknum;
	unsigned char      tcph_reserved:4, tcph_offset:4;
	// unsigned char tcph_flags;
	unsigned int
	   tcp_res1:4,      /*little-endian*/
	   tcph_hlen:4,     /*length of tcp header in 32-bit words*/
	   tcph_fin:1,      /*Finish flag "fin"*/
	   tcph_syn:1,       /*Synchronize sequence numbers to start a connection*/
	   tcph_rst:1,      /*Reset flag */
	   tcph_psh:1,      /*Push, sends data to the application*/
	   tcph_ack:1,      /*acknowledge*/
	   tcph_urg:1,      /*urgent pointer*/
	   tcph_res2:2;
	unsigned short int tcph_win;
	unsigned short int tcph_chksum;
	unsigned short int tcph_urgptr;
};

void gen_tcp(struct tcp_header *tcp, unsigned short int srcport, unsigned short int destport, unsigned short int chksum) {
	tcp -> tcph_srcport = srcport;
	tcp -> tcph_destport = destport;
	tcp -> tcph_seqnum = htonl(1);
	tcp -> tcph_acknum = 0;
	tcp -> tcph_offset = 5;
	tcp -> tcph_syn = 1;
	tcp -> tcph_ack = 0;
	tcp -> tcph_win = htons(32767);
	//tcp -> tcph_chksum = 0; // Done by kernel
	tcp -> tcph_chksum = chksum;
	tcp -> tcph_urgptr = 0;
}

#endif // TCP_H_