#pragma once

#include <memory>

#include "otus_course_project_lib/interfaces/i_packet.hpp"

#include <boost/lockfree/spsc_queue.hpp>

namespace packet_analyzer
{
	using spsc_packet_queue = boost::lockfree::spsc_queue<std::shared_ptr<i_packet>>;

	class packet_processor
	{
	public:
		explicit packet_processor(std::shared_ptr<spsc_packet_queue> packet_queue);

	private:
		void start();

		std::shared_ptr<spsc_packet_queue> packet_queue_;
	};
}
