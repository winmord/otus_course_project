#include "otus_course_project_lib/states/pause_state.hpp"

#include "otus_course_project_lib/handlers/abstract_handler.hpp"
#include "otus_course_project_lib/handlers/save_packet_handler.hpp"

namespace packet_analyzer
{
	pause_state::pause_state(std::shared_ptr<std::shared_ptr<i_state>> previous_state,
	                         std::shared_ptr<spsc_packet_queue> packet_queue)
		: previous_state_(std::move(previous_state)), packet_queue_(std::move(packet_queue))
	{
		this->pause_packet_queue_ = std::make_shared<spsc_packet_queue>(1'000'000);
		const auto save_handler = std::make_shared<save_packet_handler>(pause_packet_queue_);
		this->handler_ = std::make_shared<abstract_handler>()->set_next(save_handler);
	}

	void pause_state::to()
	{
		auto packet_consumer = [this](std::shared_ptr<i_packet> const& packet)
		{
			this->handler_->handle(packet);
		};

		this->packet_queue_->consume_one(packet_consumer);
	}
}
