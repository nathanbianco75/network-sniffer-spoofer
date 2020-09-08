#ifndef SIMPLE_CHECKSUM_H_
#define SIMPLE_CHECKSUM_H_

// Simple checksum function, may use others such as Cyclic Redundancy Check, CRC
unsigned short csum(unsigned short *buf, int len)
{
	unsigned long sum;

	for (sum=0; len>0; len--)
			sum += *buf++;
		
	sum = (sum >> 16) + (sum &0xffff);
	sum += (sum >> 16);

	return (unsigned short)(~sum);
}

#endif // SIMPLE_CHECKSUM_H_