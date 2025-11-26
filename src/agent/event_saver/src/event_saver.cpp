#include <event_saver.hpp>

#include <logger.hpp>

#include <exception>

namespace event_saver
{
    EventSaver::EventSaver(bool enabled, std::filesystem::path filePath)
        : m_enabled(enabled)
        , m_filePath(std::move(filePath))
    {
        if (m_enabled)
        {
            try
            {
                // Ensure parent directory exists
                if (m_filePath.has_parent_path() && !m_filePath.parent_path().empty())
                {
                    std::filesystem::create_directories(m_filePath.parent_path());
                }

                // Open file in append mode
                m_outputFile.open(m_filePath, std::ios::out | std::ios::app);

                if (!m_outputFile.is_open())
                {
                    LogError("Failed to open event file: {}", m_filePath.string());
                    m_enabled = false;
                }
                else
                {
                    LogInfo("Event saving enabled. Saving to: {}", m_filePath.string());
                }
            }
            catch (const std::exception& e)
            {
                LogError("Failed to initialize event saver: {}", e.what());
                m_enabled = false;
            }
        }
    }

    EventSaver::~EventSaver()
    {
        if (m_outputFile.is_open())
        {
            m_outputFile.close();
        }
    }

    bool EventSaver::SaveEvents(const std::string& events)
    {
        if (!m_enabled || events.empty())
        {
            return !m_enabled; // Return true if disabled (nothing to do), false if enabled but empty
        }

        const std::lock_guard<std::mutex> lock(m_mutex);

        try
        {
            if (!m_outputFile.is_open())
            {
                m_outputFile.open(m_filePath, std::ios::out | std::ios::app);
                if (!m_outputFile.is_open())
                {
                    LogError("Failed to reopen event file: {}", m_filePath.string());
                    return false;
                }
            }

            m_outputFile << events << "\n";
            m_outputFile.flush();

            LogTrace("Events saved to file: {}", m_filePath.string());
            return true;
        }
        catch (const std::exception& e)
        {
            LogError("Failed to save events: {}", e.what());
            return false;
        }
    }

    bool EventSaver::IsEnabled() const
    {
        return m_enabled;
    }
} // namespace event_saver
