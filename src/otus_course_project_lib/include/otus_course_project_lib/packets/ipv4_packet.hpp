#pragma once

#include "otus_course_project_lib/interfaces/i_packet.hpp"

namespace packet_analyzer
{
	class ipv4_packet : public i_packet
	{
	public:
		ipv4_packet(std::vector<uint8_t> bytes, const int id);
		
		std::vector<uint8_t> get_bytes() const override;
		int get_id() override;

	private:
		void parse_bytes();
		
		std::vector<uint8_t> bytes_;
		int id_;

		uint8_t version_;
		uint8_t header_length_;
		uint16_t packet_size_;
		uint8_t protocol_;
	};
}
