#pragma once

#include <boost/lockfree/spsc_queue.hpp>

#include "otus_course_project_lib/handlers/abstract_handler.hpp"
#include "otus_course_project_lib/interfaces/i_state.hpp"

namespace packet_analyzer
{
	using spsc_packet_queue = boost::lockfree::spsc_queue<std::shared_ptr<i_packet>>;
	
	class save_packet_handler : public abstract_handler
	{
	public:
		save_packet_handler(std::shared_ptr<spsc_packet_queue> packet_queue);
		
		void handle(const std::shared_ptr<i_packet> packet) override;

	private:
		static bool is_control_packet(std::shared_ptr<i_packet> const& packet);

		std::shared_ptr<spsc_packet_queue> packet_queue_;
	};
}
