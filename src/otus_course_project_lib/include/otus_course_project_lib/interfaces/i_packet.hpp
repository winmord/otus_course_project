#pragma once

#include <vector>

namespace packet_analyzer
{
	class i_packet
	{
	public:
		virtual ~i_packet() = default;
		virtual std::vector<uint8_t> get_bytes() = 0;
	};
}