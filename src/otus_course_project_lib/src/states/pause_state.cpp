#include "otus_course_project_lib/states/pause_state.hpp"

#include "otus_course_project_lib/handlers/abstract_handler.hpp"
#include "otus_course_project_lib/handlers/save_packets_handler.hpp"
#include "otus_course_project_lib/handlers/continue_packet_handler.hpp"

namespace packet_analyzer
{
	pause_state::pause_state(std::shared_ptr<std::shared_ptr<i_state>> state,
	                         std::shared_ptr<i_state> previous_state,
	                         std::shared_ptr<spsc_packet_queue> packet_queue)
		: state_(std::move(state)),
		  previous_state_(std::move(previous_state)),
		  packet_queue_(std::move(packet_queue))
	{
		this->setup_handlers();
	}

	void pause_state::to()
	{
		auto packet_consumer = [this](std::shared_ptr<i_packet> const& packet)
		{
			this->handler_->handle(packet);
		};

		this->packet_queue_->consume_one(packet_consumer);
	}

	void pause_state::setup_handlers()
	{
		this->handler_ = std::make_shared<abstract_handler>();
		const auto save_handler = std::make_shared<save_packets_handler>(this->packet_queue_);
		const auto continue_handler = std::make_shared<continue_packet_handler>(
			this->state_,
			this->previous_state_
		);

		this->handler_->set_next(save_handler)->set_next(continue_handler);
	}
}
