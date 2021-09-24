#pragma once
#include <memory>
#include <boost/lockfree/spsc_queue.hpp>

#include "otus_course_project_lib/interfaces/i_packet.hpp"
#include "otus_course_project_lib/interfaces/i_state.hpp"

namespace packet_analyzer
{
	using spsc_packet_queue = boost::lockfree::spsc_queue<std::shared_ptr<i_packet>>;
	
	class drop_state : public i_state
	{
	public:
		explicit drop_state(std::shared_ptr<spsc_packet_queue> packet_queue);
		
		void to() override;

	private:
		std::shared_ptr<spsc_packet_queue> packet_queue_;
	};
}
