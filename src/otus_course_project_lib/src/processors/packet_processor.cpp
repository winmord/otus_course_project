#include "otus_course_project_lib/processors/packet_processor.hpp"

namespace packet_analyzer
{
	packet_processor::packet_processor(std::shared_ptr<spsc_packet_queue> packet_queue)
		: packet_queue_(std::move(packet_queue))
	{
	}

	void packet_processor::start()
	{

	}
}