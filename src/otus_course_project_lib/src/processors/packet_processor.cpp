#include "otus_course_project_lib/processors/packet_processor.hpp"

namespace packet_analyzer
{
	packet_processor::packet_processor(std::shared_ptr<std::shared_ptr<i_state>> state,
	                                   std::shared_ptr<spsc_packet_queue> packet_queue)
		: state_(std::move(state)), packet_queue_(std::move(packet_queue))
	{
		this->start();
	}

	bool packet_processor::is_started() const
	{
		return this->is_started_;
	}

	packet_processor::~packet_processor()
	{
		this->stop();
		this->packet_processor_thread_.join();
	}

	void packet_processor::start()
	{
		this->is_started_ = true;

		this->packet_processor_thread_ = std::thread([&]()
			{
				while (*this->state_ != nullptr)
				{
					this->state_->get()->to();
				}

				this->is_started_ = false;
			}
		);
	}

	void packet_processor::stop()
	{
		this->is_started_ = false;
	}
}
