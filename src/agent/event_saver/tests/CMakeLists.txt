find_package(GTest CONFIG REQUIRED)

add_executable(event_saver_test event_saver_test.cpp)

configure_target(event_saver_test)

target_include_directories(event_saver_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/mocks)

target_link_libraries(event_saver_test PRIVATE EventSaver GTest::gtest GTest::gmock)

add_test(NAME EventSaverTest COMMAND event_saver_test)
