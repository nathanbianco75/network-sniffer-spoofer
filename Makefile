CC = gcc
CFLAGS = -Wall
DEPS = src/headers/*.h
OBJ = sniffer.o ethernet_header.o icmp_header.o ip_header.o simple_checksum.o tcp_header.o udp_header.o util_sniff.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o sniffex.c -lpcap $@ $<

sniffer: $(OBJ)
	gcc $(CFLAGS) -o $@ $^