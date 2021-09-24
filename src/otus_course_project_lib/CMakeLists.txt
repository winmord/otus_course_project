cmake_minimum_required(VERSION 3.0.0)
project(otus_course_project_lib C CXX)

set(CMAKE_CXX_STANDARD 17)
if(MSVC)
    add_definitions(-D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS)
endif()

if(MSVC)
    add_definitions(/wd4251 /wd4275 /wd4003 /wd4005 /wd4503 /wd4290 -D_SCL_SECURE_NO_WARNINGS)
else ()
    message("not ready for non-msvc compilation")
endif ()

include_directories(${otus_course_project_lib_SOURCE_DIR}/include)

set(SOURCE_FILES
		include/otus_course_project_lib/collectors/statistic_collector.hpp

		include/otus_course_project_lib/interfaces/i_handler.hpp
		include/otus_course_project_lib/interfaces/i_packet.hpp
		include/otus_course_project_lib/interfaces/i_state.hpp

		include/otus_course_project_lib/handlers/abstract_handler.hpp
		include/otus_course_project_lib/handlers/continue_packet_handler.hpp
		include/otus_course_project_lib/handlers/ipv4_packet_handler.hpp
		include/otus_course_project_lib/handlers/ipv6_packet_handler.hpp
		include/otus_course_project_lib/handlers/pause_packet_handler.hpp
		include/otus_course_project_lib/handlers/save_packets_handler.hpp
		include/otus_course_project_lib/handlers/stop_packet_handler.hpp

		include/otus_course_project_lib/handlers/ipv4_protocols/tcp_handler.hpp

		include/otus_course_project_lib/packets/continue_packet.hpp
		include/otus_course_project_lib/packets/control_packet_ids.hpp
		include/otus_course_project_lib/packets/ipv4_packet.hpp
		include/otus_course_project_lib/packets/pause_packet.hpp
		include/otus_course_project_lib/packets/stop_packet.hpp

		include/otus_course_project_lib/processors/packet_processor.hpp

		include/otus_course_project_lib/providers/statistic_collector_provider.hpp

		include/otus_course_project_lib/states/drop_state.hpp
		include/otus_course_project_lib/states/handle_state.hpp

		src/collectors/statistic_collector.cpp

		src/handlers/abstract_handler.cpp
		src/handlers/continue_packet_handler.cpp
		src/handlers/ipv4_packet_handler.cpp
		src/handlers/ipv6_packet_handler.cpp
		src/handlers/pause_packet_handler.cpp
		src/handlers/save_packets_handler.cpp
		src/handlers/stop_packet_handler.cpp

		src/handlers/ipv4_protocols/tcp_handler.cpp
		
		src/packets/continue_packet.cpp
		src/packets/ipv4_packet.cpp
		src/packets/pause_packet.cpp
		src/packets/stop_packet.cpp

		src/processors/packet_processor.cpp

		src/providers/statistic_collector_provider.cpp

		src/states/drop_state.cpp
		src/states/handle_state.cpp
		src/states/pause_state.cpp
	)

source_group(TREE ${PROJECT_SOURCE_DIR} FILES ${SOURCE_FILES})
	
add_library(otus_course_project_lib ${SOURCE_FILES})
target_link_libraries(otus_course_project_lib ${CONAN_LIBS})