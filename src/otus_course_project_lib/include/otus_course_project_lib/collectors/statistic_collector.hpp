#pragma once
#include <list>
#include <map>
#include <string>

namespace packet_analyzer
{
	class statistic_collector
	{
	public:
		std::list<int> get_value(std::string const& key);
		void set_value(std::string const& key, const int value);

		void drop_statistic();
		
	private:
		std::map<std::string, std::list<int>> statistic_;
	};
}
