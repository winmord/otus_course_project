#include "otus_course_project_lib/collectors/statistic_collector.hpp"

#include <stdexcept>

namespace packet_analyzer
{
	std::list<int> statistic_collector::get_value(std::string const& key)
	{
		if (this->statistic_.find(key) != this->statistic_.end())
		{
			return this->statistic_.at(key);
		}

		throw std::runtime_error("No data for key \"" + key + "\"");
	}

	void statistic_collector::set_value(std::string const& key, const int value)
	{
		const auto lb = this->statistic_.lower_bound(key);

		if (lb != this->statistic_.end())
		{
			lb->second.emplace_back(value);
		}
		else
		{
			this->statistic_.insert({key, {value}});
		}
	}

	void statistic_collector::drop_statistic()
	{
		this->statistic_.clear();
	}
}
