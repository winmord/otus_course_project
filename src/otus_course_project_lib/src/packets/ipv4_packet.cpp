#include "otus_course_project_lib/packets/ipv4_packet.hpp"

#include <utility>

namespace packet_analyzer
{
	ipv4_packet::ipv4_packet(std::vector<uint8_t> bytes, const int id)
		: bytes_(std::move(bytes)), id_(id)
	{
		parse_bytes();
	}

	std::vector<uint8_t> ipv4_packet::get_bytes() const
	{
		return this->bytes_;
	}

	int ipv4_packet::get_id()
	{
		return this->id_;
	}

	void ipv4_packet::parse_bytes()
	{
		this->version_ = this->bytes_[0] >> 4;
		this->header_length_ = this->bytes_[0] & 0x0f;
		this->packet_size_ = (this->bytes_[2] << 8) | this->bytes_[3];
		this->protocol_ = this->bytes_[9];
	}
}
