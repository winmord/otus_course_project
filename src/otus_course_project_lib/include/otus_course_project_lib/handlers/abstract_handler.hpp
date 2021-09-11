#pragma once

#include "otus_course_project_lib/interfaces/i_handler.hpp"

namespace packet_analyzer
{
	class abstract_handler : public i_handler
	{
	public:
		std::shared_ptr<i_handler> set_next(std::shared_ptr<i_handler> handler) override;
		void handle(std::shared_ptr<i_packet> packet) override;

	private:
		std::shared_ptr<i_handler> next_handler_;
	};
}
