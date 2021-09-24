#pragma once

#include "otus_course_project_lib/handlers/abstract_handler.hpp"

namespace packet_analyzer
{
	class ipv6_packet_handler : public abstract_handler
	{
	public:
		void handle(const std::shared_ptr<i_packet> packet) override;

	private:
		static bool is_ipv6_packet(std::shared_ptr<i_packet> const& packet);
	};
}