#pragma once

#include <memory>

#include "otus_course_project_lib/interfaces/i_packet.hpp"

namespace packet_analyzer
{
	class i_handler
	{
	public:
		virtual ~i_handler() = default;
		virtual std::shared_ptr<i_handler> set_next(std::shared_ptr<i_handler> handler) = 0;
		virtual void handle(const std::shared_ptr<i_packet> packet) = 0;
	};
}
