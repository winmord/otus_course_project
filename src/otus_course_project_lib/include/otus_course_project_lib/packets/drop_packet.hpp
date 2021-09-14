#pragma once

#include "otus_course_project_lib/interfaces/i_packet.hpp"

namespace packet_analyzer
{
	class drop_packet : public i_packet
	{
	public:
		std::vector<uint8_t> get_bytes() override;
		int get_id() override;
	};
}
