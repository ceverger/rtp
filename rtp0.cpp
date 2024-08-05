#include "rtp0.hpp"

	namespace Rtp
	{

		void Header::getV() const
		{
			/* Получение значения версии протокола */

				uint8_t v = (header[0] >> 6) & 0x03;
				
				return v;			
		}

		uint8_t Header::getP() const
		{	
			/* Получение значения дополнения заголовка RTP */

				uint8_t p = (header[0] >> 5) & 0x01;

				return p;		
		}

		uint8_t Header::getX() const
		{
			/* Получение значения расширения заголовка RTP */

				uint8_t x = (header[0] >> 4) & 0x01;

				return x;
		}

		uint8_t Header::getCC() const
		{
			/* Получение количества источников синхронизации */

				uint8_t cc = header[0] & 0x0F;

				return cc;
		}

		uint8_t Header::getM() const
		{	
			/* Получение значения бита маркера заголовка RTP */

				uint8_t m = (header[1] >> 7)  & 0x01;

				return m;	
		}

		uint8_t Header::getPT() const
		{
			/* Получение типа полезной нагрузки заголовка RTP */

				uint8_t pt = header[1] & 0x7F;

				return pt;		
		}

		uint16_t Header::getSEQ() const
		{
			/* Получение значения номера RTP-пакета */

				uint16_t seq = header[2];

				seq = (seq << 8) | header[3];

				return seq;
		}

		uint32_t Header::getTS() const
		{
			/* Получение временной метки RTP-пакета */

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

		uint32_t Header::getSSRC() const
		{
			/* Получение номера источника синхронизации */

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

		int Header::getHeader(Header & header) const
		{
			/* Копирование данных заголовка RTP-пакета в другой объект заголовка RTP-пакета */

				if(!isInit()) return -1;
				if(getSize() < HeaderSize) return -1;
				if(header.isInit() == false) return -1;
				if(header.getSize() < HeaderSize ) return 0;

				int i = 0;

				while(i < header.getSize())
				{
					header.m_pos[i] = m_pos[i];
					i++;
				}

				return i;
		}

		void RTPHeader::setV(uint8_t v)
		{
			/* Установка версии RTP-протокола */

				if(!isInit()) return;
				if(getSize() < HeaderSize) return;

				header[0] = ((v << 6) & 0xC0) | (header[0] & 0x3F);
		}

		void RTPHeader::setP(uint8_t p)
		{
			/* Установка значения дополнения заголовка RTP */

				if(!isInit()) return;
				if(getSize() < HeaderSize) return;

				header[0] = ((p << 5) & 0x20) | (header[0] & 0xDF);
		}

		void RTPHeader::setX(uint8_t x)
		{
			/* Установка значения расширения заголовка RTP  */

				if(!isInit()) return;
				if(getSize() < HeaderSize) return;

				header[0] = ((x << 4) & 0x10) | (header[0] & 0xEF);
		}

		void RTPHeader::setCC(uint8_t cc)
		{
			/* Установка значения количества источников синхронизации RTP-потока */

				if(!isInit()) return;
				if(getSize() < HeaderSize) return;

				header[0] = (cc & 0x0F) | (header[0] & 0xF0);
		}

		void RTPHeader::setM(uint8_t m)
		{
			/* Установка значения бита маркера заголовка RTP */

				if(!isInit()) return;
				if(getSize() < HeaderSize) return;

				header[1] = ((m << 7) & 0x80) | (header[1] & 0x7F);
		}

		void RTPHeader::setPT(uint8_t pt)
		{
			/* Установка значения типа полезной нагрузки заголовка RTP */

				if(!isInit()) return;
				if(getSize() < HeaderSize) return;

				header[1] = (pt & 0x7F) | (header[1] & 0x80);
		}

		void RTPHeader::setSEQ(uint16_t seq)
		{
			/* Установка значения номера RTP-пакета */

				if(!isInit()) return;
				if(getSize() < HeaderSize) return;

				header[2] = (seq >> 8) & 0x00FF;
				header[3] = seq & 0x00FF;
		}

		void RTPHeader::setTS(uint32_t ts)
		{
			/* Установка значения временной метки RTP-пакета */

				if(!isInit()) return;
				if(getSize() < HeaderSize) return;

				header[4] = (ts >> 24) & 0x000000FF;
				header[5] = (ts >> 16) & 0x000000FF;
				header[6] = (ts >>  8) & 0x000000FF;
				header[7] =  ts & 0x000000FF;
		}

		void RTPHeader::setSSRC(uint32_t ssrc)
		{
			/* Установка значения номера источника синхронизации */

				if(!isInit()) return;
				if(getSize() < HeaderSize) return;

				header[8]  = (ssrc >> 24) & 0x000000FF;
				header[9]  = (ssrc >> 16) & 0x000000FF;
				header[10] = (ssrc >> 8)  & 0x000000FF;
				header[11] =  ssrc & 0x000000FF;
		}	

	}; // namespace Rtp
