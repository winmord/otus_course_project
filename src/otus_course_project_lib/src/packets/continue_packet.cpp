#include "otus_course_project_lib/packets/continue_packet.hpp"

#include <stdexcept>

#include "otus_course_project_lib/packets/control_packet_ids.hpp"

namespace packet_analyzer
{
	std::vector<uint8_t> continue_packet::get_bytes()
	{
		throw std::runtime_error("This is continue packet");
	}

	int continue_packet::get_id()
	{
		return static_cast<int>(control_packet_ids::continue_packet_id);
	}
}
