#include "otus_course_project_lib/handlers/continue_packet_handler.hpp"

#include "otus_course_project_lib/packets/control_packet_ids.hpp"
#include "otus_course_project_lib/states/pause_state.hpp"

namespace packet_analyzer
{
	continue_packet_handler::continue_packet_handler(std::shared_ptr<std::shared_ptr<i_state>> state,
	                                                 std::shared_ptr<spsc_packet_queue> packet_queue)
		: state_(std::move(state)), packet_queue_(std::move(packet_queue))
	{
	}

	void continue_packet_handler::handle(const std::shared_ptr<i_packet> packet)
	{
		if (is_continue_packet(packet))
		{
			*this->state_ = std::make_shared<pause_state>(this->state_, this->packet_queue_);
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
