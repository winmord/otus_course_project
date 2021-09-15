#include <catch2/catch.hpp>
#include <fakeit.hpp>

#include <condition_variable>
#include <boost/lockfree/spsc_queue.hpp>

#include <otus_course_project_lib/providers/statistic_collector_provider.hpp>
#include <otus_course_project_lib/interfaces/i_packet.hpp>
#include <otus_course_project_lib/processors/packet_processor.hpp>
#include <otus_course_project_lib/states/handle_state.hpp>

#include <otus_course_project_lib/handlers/ipv4_packet_handler.hpp>
#include <otus_course_project_lib/handlers/pause_packet_handler.hpp>
#include <otus_course_project_lib/handlers/stop_packet_handler.hpp>

#include <otus_course_project_lib/packets/continue_packet.hpp>
#include <otus_course_project_lib/packets/pause_packet.hpp>
#include <otus_course_project_lib/packets/stop_packet.hpp>

using namespace fakeit;
using namespace packet_analyzer;

void wait_packet_processor_finish(packet_processor const& p_processor)
{
	auto processor_is_started{true};
	std::condition_variable executor_finish_condition;

	auto executor_finish_checker = std::thread([&]()
		{
			while (processor_is_started)
			{
				processor_is_started = p_processor.is_started();
				if (!processor_is_started) executor_finish_condition.notify_one();
			}
		}
	);

	std::mutex m;
	std::unique_lock<std::mutex> locker(m);

	executor_finish_condition.wait(locker, [&]()
	                               {
		                               return !processor_is_started;
	                               }
	);

	if (executor_finish_checker.joinable()) executor_finish_checker.join();
}

TEST_CASE("stop packet processor test")
{
	statistic_collector_provider::stat_collector.drop_statistic();

	auto packet_id{0};

	Mock<i_packet> i_packet_mock;
	When(Method(i_packet_mock, get_id)).AlwaysDo([&]() { return packet_id++; });
	When(Method(i_packet_mock, get_bytes)).AlwaysReturn(
		std::vector<uint8_t>{0x45, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	);

	const auto pointer_to_packet = std::shared_ptr<i_packet>(&i_packet_mock(), [](...)
	{
	});

	const auto packet_queue = std::make_shared<boost::lockfree::spsc_queue<std::shared_ptr<i_packet>>>(10);
	const auto abs_handler = std::make_shared<abstract_handler>();

	auto state = std::make_shared<handle_state>(packet_queue, abs_handler);
	const auto pointer_to_state = std::make_shared<std::shared_ptr<i_state>>(state);

	const auto ipv4_handler = std::make_shared<ipv4_packet_handler>();
	const auto stop_handler = std::make_shared<stop_packet_handler>(pointer_to_state);

	abs_handler->set_next(ipv4_handler)->set_next(stop_handler);

	const packet_processor p_processor(pointer_to_state, packet_queue);

	packet_queue->push(pointer_to_packet);

	const auto s_packet = std::make_shared<stop_packet>();

	packet_queue->push(s_packet);
	packet_queue->push(pointer_to_packet);

	wait_packet_processor_finish(p_processor);


	REQUIRE_NOTHROW(statistic_collector_provider::stat_collector.get_value("IPv4"));
	REQUIRE_FALSE(packet_queue->empty());
}

TEST_CASE("pause/continue packet processor test")
{
	statistic_collector_provider::stat_collector.drop_statistic();

	auto packet_id{0};

	Mock<i_packet> i_packet_mock;
	When(Method(i_packet_mock, get_id)).AlwaysDo([&]() { return packet_id++; });
	When(Method(i_packet_mock, get_bytes)).AlwaysReturn(
		std::vector<uint8_t>{0x45, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	);

	const auto pointer_to_packet = std::shared_ptr<i_packet>(&i_packet_mock(), [](...)
	{
	});

	const auto packet_queue = std::make_shared<boost::lockfree::spsc_queue<std::shared_ptr<i_packet>>>(10);

	const auto abs_handler = std::make_shared<abstract_handler>();
	auto state = std::make_shared<handle_state>(packet_queue, abs_handler);
	const auto pointer_to_state = std::make_shared<std::shared_ptr<i_state>>(state);

	const auto ipv4_handler = std::make_shared<ipv4_packet_handler>();
	const auto pause_handler = std::make_shared<pause_packet_handler>(pointer_to_state, packet_queue);
	const auto stop_handler = std::make_shared<stop_packet_handler>(pointer_to_state);

	abs_handler->set_next(ipv4_handler)->set_next(pause_handler)->set_next(stop_handler);

	const packet_processor p_processor(pointer_to_state, packet_queue);

	const auto c_packet = std::make_shared<continue_packet>();
	const auto p_packet = std::make_shared<pause_packet>();
	const auto s_packet = std::make_shared<stop_packet>();

	packet_queue->push(p_packet);
	packet_queue->push(pointer_to_packet);

	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	REQUIRE_FALSE(packet_queue->empty());
	REQUIRE_THROWS_WITH(statistic_collector_provider::stat_collector.get_value("IPv4"), "No data for key \"IPv4\"");

	packet_queue->push(c_packet);

	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	packet_queue->push(s_packet);

	wait_packet_processor_finish(p_processor);

	REQUIRE_NOTHROW(statistic_collector_provider::stat_collector.get_value("IPv4"));
	REQUIRE(packet_queue->empty());
}

