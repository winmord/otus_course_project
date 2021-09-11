#include "otus_course_project_lib/handlers/stop_packet_handler.hpp"

namespace packet_analyzer
{
	stop_packet_handler::stop_packet_handler(std::shared_ptr<std::shared_ptr<i_state>> state)
		: state_(std::move(state))
	{
	}

	void stop_packet_handler::handle(const std::shared_ptr<i_packet> packet)
	{
		if(is_stop_packet(packet))
		{
			*this->state_ = nullptr;
		}
		else
		{
			abstract_handler::handle(packet);
		}
	}

	bool stop_packet_handler::is_stop_packet(std::shared_ptr<i_packet> const& packet)
	{
		return packet->get_id() == -1;
	}
}
