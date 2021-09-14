#include "otus_course_project_lib/packets/pause_packet.hpp"

#include <stdexcept>

#include "otus_course_project_lib/packets/control_packet_ids.hpp"

namespace packet_analyzer
{
	std::vector<uint8_t> pause_packet::get_bytes()
	{
		throw std::runtime_error("This is pause packet");
	}

	int pause_packet::get_id()
	{
		return static_cast<int>(control_packet_ids::stop_packet_id);
	}
}
