#pragma once

namespace packet_analyzer
{
	enum class control_packet_ids : int
	{
		stop_packet_id = -1,
		drop_packet_id = -2
	};
}
