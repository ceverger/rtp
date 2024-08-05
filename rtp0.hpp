#include <stdint.h>
#include "byte.hpp"

#ifndef RTP_HPP
#define RTP_HPP

	namespace Rtp 
	{
		/* Пространство имён модуля для работы с RTP-потоком */

		class Header : public Byte::Buffer
		{
			/* Данный класс предназначен для работы с заголовком RTP-пакета */

			public:
	
			// Основные целочисленные идентификаторы класса

				enum { HeaderSize = 12; } // Минимальный размер заголовка rtp-пакета

			// Конструкторы и деструкторы класса

				Header() : Buffer() {}
				virtual ~Header() {}

			// Селекторы класса

				 uint8_t getV()    const;
				 uint8_t getP()    const;
				 uint8_t getX()    const;
				 uint8_t getCC()   const;
				 uint8_t getM()    const;
				 uint8_t getPT()   const;
				uint16_t getSEQ()  const;
				uint32_t getTS()   const;
				uint32_t getSSRC() const;

				int getHeader(Header & header) const;

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

				void setHeader(const Header & header);

		}; // class Header

		class Packet : public Byte::Buffer
		{
			private:

				uint8_t *h_end; // Указатель на конечную позиция части буфера, в которой хранится заголовок rtp-пакета
			
			public:

				// Конструкторы и деструкторы класса

					Packet();
					virtual ~Packet() {}

				// Селекторы класса

					int getHeaderSize() const { return h_end - m_pos; }
					int getHeader(uint8_t *buf, int bufsize) const;

					int getPayloadSize() const { return m_end - h_end; }
					int getPayload(uint8_t *buf, int bufsize) const;

				// Модификаторы класса

					void setHeader(uint8_t *buf, int len);
					void setPayload(uint8_t *buf, int len);

				// Другие методы класса
					
					void init();
					void reset();

		}; // class Packet

	}; // namespace Rtp

#endif // RTP_HPP
