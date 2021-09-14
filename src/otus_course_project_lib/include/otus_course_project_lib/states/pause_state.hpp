#pragma once

#include "otus_course_project_lib/interfaces/i_state.hpp"
#include "otus_course_project_lib/interfaces/i_packet.hpp"
#include "otus_course_project_lib/interfaces/i_handler.hpp"

#include <boost/lockfree/spsc_queue.hpp>

namespace packet_analyzer
{
	using spsc_packet_queue = boost::lockfree::spsc_queue<std::shared_ptr<i_packet>>;

	class pause_state : public i_state
	{
	public:
		explicit pause_state(std::shared_ptr<std::shared_ptr<i_state>> previous_state,
		                     std::shared_ptr<spsc_packet_queue> packet_queue);

		void to() override;

	private:
		std::shared_ptr<std::shared_ptr<i_state>> previous_state_;
		std::shared_ptr<spsc_packet_queue> packet_queue_;
		std::shared_ptr<spsc_packet_queue> pause_packet_queue_;
		std::shared_ptr<i_handler> handler_;
	};
}
