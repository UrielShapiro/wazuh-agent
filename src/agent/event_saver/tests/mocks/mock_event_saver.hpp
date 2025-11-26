#pragma once

#include <ievent_saver.hpp>

#include <gmock/gmock.h>

#include <string>

class MockEventSaver : public event_saver::IEventSaver
{
public:
    MOCK_METHOD(bool, SaveEvents, (const std::string& events), (override));
    MOCK_METHOD(bool, IsEnabled, (), (const, override));
};
