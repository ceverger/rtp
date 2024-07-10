#include <stdint.h>

#ifndef RTP_HPP
#define RTP_HPP

#define HEADER_SIZE 12 // Максимальный размер буфера с данными rtp-заголовка

	class RTPHeader
	{
		private:

			uint8_t header[HEADER_SIZE]; // Буфер с данными rtp-заголовка

		public:

			// Конструкторы и деструкторы класса

				RTPHeader();
				virtual ~RTPHeader() {}

			// Селекторы класса

				     int getSize() const { return HEADER_SIZE; }

				 uint8_t getV()    const;
				 uint8_t getP()    const;
				 uint8_t getX()    const;
				 uint8_t getCC()   const;
				 uint8_t getM()    const;
				 uint8_t getPT()   const;
				uint16_t getSEQ()  const;
				uint32_t getTS()   const;
				uint32_t getSSRC() const;

				     int getHeader(uint8_t *buf, int bufsize) const;

			// Модификаторы класса

				void setV(uint8_t v);
				void setP(uint8_t p);
				void setX(uint8_t x);
				void setCC(uint8_t cc);
				void setM(uint8_t m);
				void setPT(uint8_t pt);
				void setSEQ(uint16_t seq);
				void setTS(uint32_t ts);
				void setSSRC(uint32_t ssrc);

				void setHeader(
									 uint8_t v,
									 uint8_t p,
									 uint8_t x,
									 uint8_t cc,
									 uint8_t m,
									 uint8_t pt,
									 uint16_t seq,
									 uint32_t ts,
									 uint32_t ssrc
						        );

				void setHeader(uint8_t *buf, int bufsize);

			// Другие методы класса

				void reset();
			
	}; // class RTPHeader


	class RTPPacket
	{
		private:

			uint8_t *m_pos;   // Начальная позиция буфера для сохранения rtp-пакета
			uint8_t *cur;     // Текущая позиция буфера для сохранения rtp-пакета
			uint8_t *h_end; // Конечная позиция части буфера, в которой хранится заголовок rtp-пакета
			uint8_t *m_end;   // Конечная позиция буфера для сохранения rtp-пакета
		
		public:

			// Конструкторы и деструкторы класса

				RTPPacket();
				virtual ~RTPPacket() {}

			// Селекторы класса

				int getBufSize()     const { return m_end - m_pos; }
				int getBufLen()      const { return cur - m_pos;   }
				int getBufFree()     const { return m_end - cur;   }
				int getHeaderSize()  const { return h_end - m_pos; }
				int getPayloadSize() const { return m_end - h_end; }

				void getHeader(RTPHeader & header);
				int getHeader(uint8_t *buf, int bufsize);
				int getPayload(char *buf, int bufsize) const;


			// Модификаторы класса

				void setPos(uint8_t *pos);
				void setEnd(uint8_t *end);

				void setHeader(RTPHeader & header);
				void setHeader(uint8_t *buf, int bufsize);
				void setPayload(uint8_t *buf, int bufsize);

			// Другие методы класса
				
				void init();
				void reset();
				void clear();

	}; // class RTPPacket

#endif // RTP_HPP
