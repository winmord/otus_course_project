#include "otus_course_project_lib/handlers/ipv4_packet_handler.hpp"

#include <iostream>

namespace packet_analyzer
{
	void ipv4_packet_handler::handle(const std::shared_ptr<i_packet> packet)
	{
		if(is_ipv4_packet(packet))
		{
			std::cout << packet->get_id() << " is IPv4 packet" << std::endl;
		}
		else
		{
			abstract_handler::handle(packet);
		}
	}

	bool ipv4_packet_handler::is_ipv4_packet(std::shared_ptr<i_packet> const& packet)
	{
		const auto packet_bytes = packet->get_bytes();
		const auto first_byte = *packet_bytes.begin();

		return ((first_byte >> 4) == 4) && ((first_byte & 0x0f) >= 5);
	}
}
