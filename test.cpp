#include <cstdio>
#include <cstring>
#include "rtp.hpp"

int main(int argc, char *argv[])
{
	RTPPacket packet;
	RTPHeader header1, header2;

	int bufsize = 1412;
	uint8_t buf[bufsize];

	packet.setPos(buf);
	packet.setEnd(buf + bufsize);

	header1.setV(3);
	header1.setP(1);
	header1.setX(1);
	header1.setCC(5);
	header1.setM(1);
	header1.setPT(98);
	header1.setSEQ(32112);
	header1.setTS(2345987);
	header1.setSSRC(132189243);

	printf(
			 "v = %d, p = %d, x = %d, cc = %d, m = %d, pt = %d, seq = %d, ts = %d, ssrc = %d\n",
			  header1.getV(),
			  header1.getP(),
			  header1.getX(),
			  header1.getCC(),
			  header1.getM(),
			  header1.getPT(),
			  header1.getSEQ(),
			  header1.getTS(),
			  header1.getSSRC()
			);

	header1.setHeader(2, 0, 0, 2, 0, 96, 0, 0, 0);

	printf(
			 "v = %d, p = %d, x = %d, cc = %d, m = %d, pt = %d, seq = %d, ts = %d, ssrc = %d\n",
			  header1.getV(),
			  header1.getP(),
			  header1.getX(),
			  header1.getCC(),
			  header1.getM(),
			  header1.getPT(),
			  header1.getSEQ(),
			  header1.getTS(),
			  header1.getSSRC()		
			);

	packet.setHeader(header1);
	packet.getHeader(header2);

	printf(
			 "v = %d, p = %d, x = %d, cc = %d, m = %d, pt = %d, seq = %d, ts = %d, ssrc = %d\n",
			  header2.getV(),
			  header2.getP(),
			  header2.getX(),
			  header2.getCC(),
			  header2.getM(),
			  header2.getPT(),
			  header2.getSEQ(),
			  header2.getTS(),
			  header2.getSSRC()		
			);

	return 0;
}

