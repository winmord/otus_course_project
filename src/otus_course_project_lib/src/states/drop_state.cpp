#include "otus_course_project_lib/states/drop_state.hpp"

namespace packet_analyzer
{
	drop_state::drop_state(std::shared_ptr<spsc_packet_queue> packet_queue)
		: packet_queue_(std::move(packet_queue))
	{
	}

	void drop_state::to()
	{
		this->packet_queue_->pop();
	}
}
