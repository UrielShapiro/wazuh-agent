#include <event_saver.hpp>

#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <string>

class EventSaverTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        m_testDir = std::filesystem::temp_directory_path() / "wazuh_event_saver_test";
        std::filesystem::create_directories(m_testDir);
        m_testFile = m_testDir / "events.log";

        // Clean up any existing test file
        if (std::filesystem::exists(m_testFile))
        {
            std::filesystem::remove(m_testFile);
        }
    }

    void TearDown() override
    {
        // Clean up test directory
        if (std::filesystem::exists(m_testDir))
        {
            std::filesystem::remove_all(m_testDir);
        }
    }

    std::string ReadFileContent()
    {
        std::ifstream file(m_testFile);
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        return content;
    }

    std::filesystem::path m_testDir;
    std::filesystem::path m_testFile;
};

TEST_F(EventSaverTest, DisabledEventSaverDoesNotSave)
{
    event_saver::EventSaver saver(false, m_testFile);

    EXPECT_FALSE(saver.IsEnabled());
    EXPECT_TRUE(saver.SaveEvents("test event"));

    // File should not be created when disabled
    EXPECT_FALSE(std::filesystem::exists(m_testFile));
}

TEST_F(EventSaverTest, EnabledEventSaverSavesEvents)
{
    event_saver::EventSaver saver(true, m_testFile);

    EXPECT_TRUE(saver.IsEnabled());
    EXPECT_TRUE(saver.SaveEvents("test event"));

    // File should exist and contain the event
    EXPECT_TRUE(std::filesystem::exists(m_testFile));
    EXPECT_EQ(ReadFileContent(), "test event\n");
}

TEST_F(EventSaverTest, EventSaverAppendsMultipleEvents)
{
    event_saver::EventSaver saver(true, m_testFile);

    EXPECT_TRUE(saver.SaveEvents("event 1"));
    EXPECT_TRUE(saver.SaveEvents("event 2"));
    EXPECT_TRUE(saver.SaveEvents("event 3"));

    std::string expected = "event 1\nevent 2\nevent 3\n";
    EXPECT_EQ(ReadFileContent(), expected);
}

TEST_F(EventSaverTest, EventSaverCreatesParentDirectories)
{
    auto nestedPath = m_testDir / "nested" / "dir" / "events.log";
    event_saver::EventSaver saver(true, nestedPath);

    EXPECT_TRUE(saver.IsEnabled());
    EXPECT_TRUE(saver.SaveEvents("test event"));

    EXPECT_TRUE(std::filesystem::exists(nestedPath));
}

TEST_F(EventSaverTest, EmptyEventReturnsTrue)
{
    event_saver::EventSaver saver(true, m_testFile);

    // Empty events should return true but not write anything
    EXPECT_TRUE(saver.SaveEvents(""));

    // File should be created but empty (or not exist)
    if (std::filesystem::exists(m_testFile))
    {
        EXPECT_TRUE(ReadFileContent().empty());
    }
}

TEST_F(EventSaverTest, EventSaverHandlesLargeEvents)
{
    event_saver::EventSaver saver(true, m_testFile);

    // Create a large event string
    std::string largeEvent(100000, 'x');
    EXPECT_TRUE(saver.SaveEvents(largeEvent));

    std::string content = ReadFileContent();
    EXPECT_EQ(content.size(), largeEvent.size() + 1); // +1 for newline
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
