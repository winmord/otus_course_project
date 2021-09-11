#include "otus_course_project_lib/packets/stop_packet.hpp"

#include <stdexcept>

#include "otus_course_project_lib/packets/control_packet_ids.hpp"

namespace packet_analyzer
{
	std::vector<uint8_t> stop_packet::get_bytes()
	{
		throw std::runtime_error("This is stop packet");
	}

	int stop_packet::get_id()
	{
		return static_cast<int>(control_packet_ids::stop_packet_id);
	}
}
