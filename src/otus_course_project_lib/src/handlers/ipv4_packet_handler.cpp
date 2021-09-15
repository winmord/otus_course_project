#include "otus_course_project_lib/handlers/ipv4_packet_handler.hpp"

#include <memory>

#include "otus_course_project_lib/providers/statistic_collector_provider.hpp"
#include "otus_course_project_lib/packets/ipv4_packet.hpp"

namespace packet_analyzer
{
	void ipv4_packet_handler::handle(const std::shared_ptr<i_packet> packet)
	{
		if (is_ipv4_packet(packet))
		{
			statistic_collector_provider::stat_collector.
				set_value(
					std::string("IPv4"),
					packet->get_id()
				);

			const auto packet_bytes = packet->get_bytes();
			const auto protocol = std::to_string(static_cast<int>(packet_bytes[9]));

			statistic_collector_provider::stat_collector.
				set_value(
					protocol,
					packet->get_id()
				);
		}
		else
		{
			abstract_handler::handle(packet);
		}
	}

	bool ipv4_packet_handler::is_ipv4_packet(std::shared_ptr<i_packet> const& packet)
	{
		try
		{
			const auto packet_bytes = packet->get_bytes();
			const auto packet_bytes_count = packet_bytes.size();
			const auto first_byte = *packet_bytes.begin();

			const size_t version = first_byte >> 4;
			const size_t header_length = first_byte & 0x0f;

			return (version == 4) && (header_length >= 5) && (packet_bytes_count >= header_length * 4u);
		}
		catch (...)
		{
			return false;
		}
	}
}
