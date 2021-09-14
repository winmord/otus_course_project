#include "otus_course_project_lib/handlers/save_packet_handler.hpp"

#include "otus_course_project_lib/packets/control_packet_ids.hpp"

namespace packet_analyzer
{
	save_packet_handler::save_packet_handler(std::shared_ptr<spsc_packet_queue> packet_queue)
		: packet_queue_(std::move(packet_queue))
	{
	}

	void save_packet_handler::handle(const std::shared_ptr<i_packet> packet)
	{
		if(is_control_packet(packet))
		{
			abstract_handler::handle(packet);
		}
		else
		{
			this->packet_queue_->push(packet);
		}
	}

	bool save_packet_handler::is_control_packet(std::shared_ptr<i_packet> const& packet)
	{
		return packet->get_id() < 0;
	}
}
