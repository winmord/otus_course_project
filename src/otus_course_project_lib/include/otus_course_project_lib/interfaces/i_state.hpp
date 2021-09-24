#pragma once

namespace packet_analyzer
{
	class i_state
	{
	public:
		virtual ~i_state() = default;
		virtual void to() = 0;
	};
}
