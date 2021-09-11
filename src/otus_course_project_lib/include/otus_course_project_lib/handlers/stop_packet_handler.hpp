#pragma once

#include "otus_course_project_lib/handlers/abstract_handler.hpp"
#include "otus_course_project_lib/interfaces/i_state.hpp"

namespace packet_analyzer
{
	class stop_packet_handler : public abstract_handler
	{
	public:
		stop_packet_handler(std::shared_ptr<std::shared_ptr<i_state>> state);
		
		void handle(const std::shared_ptr<i_packet> packet) override;

	private:
		static bool is_stop_packet(std::shared_ptr<i_packet> const& packet);

		std::shared_ptr<std::shared_ptr<i_state>> state_;
	};
}
