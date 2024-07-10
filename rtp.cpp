#include <cstring>
#include "rtp.hpp"

	RTPHeader::RTPHeader()
	{
		bzero(header, HeaderSize);
	}

	void RTPHeader::getHeader(uint8_t *buf, int bufsize)
	{
		if(buf == nullptr || bufsize < HEADER_SIZE) return;

		for(int i = 0; i < HEADER_SIZE; ++i)
		{
			buf[i] = header[i];
		}
	}

	uint8_t RTPHeader::getV() const
	{
		uint8_t v = (header[0] >> 6) & 0x03;
		
		return v;		
	}

	uint8_t RTPHeader::getP() const
	{	
		uint8_t p = (header[0] >> 5) & 0x01;

		return p;		
	}

	uint8_t RTPHeader::getX() const
	{
		uint8_t x = (header[0] >> 4) & 0x01;

		return x;
	}

	uint8_t RTPHeader::getCC() const
	{
		uint8_t cc = header[0] & 0x0F;

		return cc;
	}

	uint8_t RTPHeader::getM() const
	{	
		uint8_t m = (header[1] >> 7)  & 0x01;

		return m;		
	}

	uint8_t RTPHeader::getPT() const
	{
		uint8_t pt = header[1] & 0x7F;

		return pt;				
	}

	uint16_t RTPHeader::getSEQ() const
	{
		uint16_t seq = header[2];

		seq = (seq << 8) | header[3];

		return seq;
	}

	uint32_t RTPHeader::getTS() const
	{
		uint32_t ts = 0;
		uint32_t temp = header[4];

		ts = (temp << 24);

		temp = header[5];

		ts |= temp << 16;

		temp = header[6];

		ts |= temp << 8;

		temp = header[7];

		ts |= temp;

		return ts;	
	}

	uint32_t RTPHeader::getSSRC() const
	{
		uint32_t ssrc = 0;
		uint32_t temp = header[8];

		ssrc = (temp << 24);

		temp = header[9];

		ssrc |= temp << 16;

		temp = header[10];

		ssrc |= temp << 8;

		temp = header[11];

		ssrc |= temp;

		return ssrc;
	}

	void RTPHeader::setV(uint8_t v)
	{
		header[0] = ((v << 6) & 0xC0) | (header[0] & 0x3F);
	}

	void RTPHeader::setP(uint8_t p)
	{
		header[0] = ((p << 5) & 0x20) | (header[0] & 0xDF);
	}

	void RTPHeader::setX(uint8_t x)
	{
		header[0] = ((x << 4) & 0x10) | (header[0] & 0xEF);
	}

	void RTPHeader::setCC(uint8_t cc)
	{
		header[0] = (cc & 0x0F) | (header[0] & 0xF0);
	}

	void RTPHeader::setM(uint8_t m)
	{
		header[1] = ((m << 7) & 0x80) | (header[1] & 0x7F);
	}

	void RTPHeader::setPT(uint8_t pt)
	{
		header[1] = (pt & 0x7F) | (header[1] & 0x80);
	}

	void RTPHeader::setSEQ(uint16_t seq)
	{
		m_pos[2] = (seq >> 8) & 0x00FF;
		m_pos[3] = seq & 0x00FF;
	}

	void RTPHeader::setTS(uint32_t ts)
	{
		m_pos[4] = (ts >> 24) & 0x000000FF;
		m_pos[5] = (ts >> 16) & 0x000000FF;
		m_pos[6] = (ts >> 8)  & 0x000000FF;
		m_pos[7] =  ts & 0x000000FF;
	}

	void RTPHeader::setSSRC(uint32_t ssrc)
	{
		m_pos[8]  = (ssrc >> 24) & 0x000000FF;
		m_pos[9]  = (ssrc >> 16) & 0x000000FF;
		m_pos[10] = (ssrc >> 8)  & 0x000000FF;
		m_pos[11] =  ssrc & 0x000000FF;
	}

	void RTPHeader::reset()
	{
		bzero(header, HeaderSize);
	}

	void RTPHeader::
		setHeader(
					  uint8_t v,
					  uint8_t p,
					  uint8_t x,
					  uint8_t cc,
					  uint8_t m,
					  uint8_t pt,
					  uint16_t seq,
					  uint32_t ts,
					  uint32_t ssrc
			      )
		{
			setV(v);
			setP(p);
			setX(x);
			setCC(cc);
			setM(m);
			setPT(pt);
			setSEQ(seq);
			setTS(ts);
			setSSRC(ssrc);
		}

	void RTPHeader::setHeader(uint8_t *buf, int bufsize)
	{
		if(buf == nullptr || bufsize < HEADER_SIZE) return;

		for(int i = 0; i < HEADER_SIZE; ++i) header[i] = buf[i];
	}


	RTPPacket::RTPPacket()
	{
		m_pos = nullptr;
		  cur = nullptr;
		h_end = nullptr;
		m_end = nullptr;
	}

	void RTPPacket::getHeader(RTPHeader & header)
	{
		if(cur == nullptr) return;

		header.setHeader(m_pos, HEADER_SIZE);
	}

	int RTPPacket::getHeader(uint8_t *buf, int bufsize) const
	{
		if(cur == nullptr || h_end == nullptr) return -1;

		int i = 0;

		cur = m_pos;

		while(i < bufsize && cur != h_end)
		{
			*buf++ = *cur++;
			 i++;
		}

		return i;
	}

	int RTPPacket::getPayload(char *buf, int bufsize) const
	{
		if(cur == nullptr || h_end == nullptr) return -1;

		int i = 0;

		cur = h_end;

		while(i < bufsize && cur != end)
		{
			*buf++ = *cur++;
			 i++;
		}

		return i;		
	}

	void RTPPacket::setPos(uint8_t *pos)
	{
		if(cur != nullptr) return;

		m_pos = pos;
	}

	void RTPPacket::setEnd(uint8_t *end)
	{
		if(cur != nullptr) return;

		m_end = end;		
	}

	void RTPPacket::setHeader(RTPHeader & header)
	{
		
	}

	void RTPPacket::setHeader(uint8_t *buf, int bufsize)
	{
		
	}

	void RTPPacket::setPayload(uint8_t *buf, int bufsize)
	{
		
	}

	void RTPPacket::init()
	{
		
	}

	void RTPPacket::reset()
	{
		
	}

	void RTPPacket::clear()
	{
		
	}
