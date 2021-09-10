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
	
	)

source_group(TREE ${PROJECT_SOURCE_DIR} FILES ${SOURCE_FILES})
	
add_library(otus_course_project_lib ${SOURCE_FILES})
target_link_libraries(otus_course_project_lib ${CONAN_LIBS})