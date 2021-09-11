#pragma once

#include "otus_course_project_lib/interfaces/i_state.hpp"
#include "otus_course_project_lib/interfaces/i_packet.hpp"
#include "otus_course_project_lib/interfaces/i_handler.hpp"

#include <boost/lockfree/spsc_queue.hpp>

namespace packet_analyzer
{
	using spsc_packet_queue = boost::lockfree::spsc_queue<std::shared_ptr<i_packet>>;

	class handle_state : public i_state
	{
	public:
		explicit handle_state(std::shared_ptr<spsc_packet_queue> packet_queue,
		                      std::shared_ptr<i_handler> handler);

		void to() override;

	private:
		std::shared_ptr<spsc_packet_queue> packet_queue_;
		std::shared_ptr<i_handler> handler_;
	};
}
