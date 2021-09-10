#pragma once

#include <memory>
#include <thread>

#include "otus_course_project_lib/interfaces/i_packet.hpp"
#include "otus_course_project_lib/interfaces/i_state.hpp"

#include <boost/lockfree/spsc_queue.hpp>

namespace packet_analyzer
{
	using spsc_packet_queue = boost::lockfree::spsc_queue<std::shared_ptr<i_packet>>;

	class packet_processor
	{
	public:
		explicit packet_processor(std::shared_ptr<std::shared_ptr<i_state>> state,
		                          std::shared_ptr<spsc_packet_queue> packet_queue);

		~packet_processor();
	
	private:
		void start();
		void stop();

		std::shared_ptr<std::shared_ptr<i_state>> state_;
		std::shared_ptr<spsc_packet_queue> packet_queue_;

		std::thread packet_processor_thread_;
		bool is_started_{false};
	};
}
