cmake_minimum_required(VERSION 3.22)

project(EventSaver)

include(../../cmake/CommonSettings.cmake)
set_common_settings()

add_library(EventSaver src/event_saver.cpp)

target_include_directories(EventSaver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(EventSaver PUBLIC Logger)

include(../../cmake/ConfigureTarget.cmake)
configure_target(EventSaver)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
