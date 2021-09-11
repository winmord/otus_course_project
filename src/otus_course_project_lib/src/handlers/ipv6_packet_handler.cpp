#include "otus_course_project_lib/handlers/ipv6_packet_handler.hpp"

#include <iostream>

namespace packet_analyzer
{
	void ipv6_packet_handler::handle(const std::shared_ptr<i_packet> packet)
	{
		if (is_ipv6_packet(packet))
		{
			std::cout << packet->get_id() << " is IPv6 packet" << std::endl;
		}
		else
		{
			abstract_handler::handle(packet);
		}
	}

	bool ipv6_packet_handler::is_ipv6_packet(std::shared_ptr<i_packet> const& packet)
	{
		const auto packet_bytes = packet->get_bytes();
		const auto first_byte = *packet_bytes.begin();

		return (first_byte >> 4) == 6;
	}
}
