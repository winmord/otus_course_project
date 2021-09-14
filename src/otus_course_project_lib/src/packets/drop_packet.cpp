#include "otus_course_project_lib/packets/drop_packet.hpp"

#include <stdexcept>

#include "otus_course_project_lib/packets/control_packet_ids.hpp"

namespace packet_analyzer
{
	std::vector<uint8_t> drop_packet::get_bytes()
	{
		throw std::runtime_error("This is drop packet");
	}

	int drop_packet::get_id()
	{
		return static_cast<int>(control_packet_ids::drop_packet_id);
	}
}
