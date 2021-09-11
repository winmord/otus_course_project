#include <catch2/catch.hpp>
#include <fakeit.hpp>

#include <otus_course_project_lib/interfaces/i_packet.hpp>

using namespace fakeit;
using namespace packet_analyzer;

TEST_CASE("stop packet processor test")
{
	auto packet_id{0};

	Mock<i_packet> i_packet_mock;
	When(Method(i_packet_mock, get_id)).AlwaysDo([&]() { return packet_id++; });
	When(Method(i_packet_mock, get_bytes)).AlwaysReturn(std::vector<uint8_t>{45});

	auto pointer_to_packet = std::shared_ptr<i_packet>(&i_packet_mock(), [](...)
	{
	});

	
}
