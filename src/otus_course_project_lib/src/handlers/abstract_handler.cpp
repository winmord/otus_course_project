#include "otus_course_project_lib/handlers/abstract_handler.hpp"

namespace packet_analyzer
{
	std::shared_ptr<i_handler> abstract_handler::set_next(std::shared_ptr<i_handler> handler)
	{
		this->next_handler_ = handler;
		
		return handler;
	}

	void abstract_handler::handle(const std::shared_ptr<i_packet> packet)
	{
		if(this->next_handler_)
		{
			this->next_handler_->handle(packet);
		}
	}
}
