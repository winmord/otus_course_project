#include "otus_course_project_lib/states/handle_state.hpp"

namespace packet_analyzer
{
	handle_state::handle_state(std::shared_ptr<spsc_packet_queue> packet_queue,
	                           std::shared_ptr<i_handler> handler)
		: packet_queue_(std::move(packet_queue)), handler_(std::move(handler))
	{
	}

	void handle_state::to()
	{
		auto packet_consumer = [this](std::shared_ptr<i_packet> const& packet)
		{
			this->handler_->handle(packet);
		};

		this->packet_queue_->consume_one(packet_consumer);
	}
}
