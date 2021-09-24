#include "otus_course_project_lib/handlers/continue_packet_handler.hpp"

#include <iostream>


#include "otus_course_project_lib/packets/control_packet_ids.hpp"
#include "otus_course_project_lib/states/pause_state.hpp"

namespace packet_analyzer
{
	continue_packet_handler::continue_packet_handler(std::shared_ptr<std::shared_ptr<i_state>> state,
	                                                 std::shared_ptr<i_state> previous_state)
		: state_(std::move(state)),
		  previous_state_(std::move(previous_state))
	{
	}

	void continue_packet_handler::handle(const std::shared_ptr<i_packet> packet)
	{
		if (is_continue_packet(packet))
		{
			*this->state_ = this->previous_state_;
		}
		else
		{
			abstract_handler::handle(packet);
		}
	}

	bool continue_packet_handler::is_continue_packet(std::shared_ptr<i_packet> const& packet)
	{
		return packet->get_id() == static_cast<int>(control_packet_ids::continue_packet_id);
	}
}
