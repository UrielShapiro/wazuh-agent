#pragma once

#include <ievent_saver.hpp>

#include <filesystem>
#include <fstream>
#include <mutex>
#include <string>

namespace event_saver
{
    /// @brief Event saver implementation that saves events to a local file
    ///
    /// This class implements the IEventSaver interface to save events to a local
    /// file. Each event batch is written as a separate line in the file.
    class EventSaver : public IEventSaver
    {
    public:
        /// @brief Constructor
        /// @param enabled Whether event saving is enabled
        /// @param filePath The path to the file where events should be saved
        EventSaver(bool enabled, std::filesystem::path filePath);

        /// @brief Destructor
        ~EventSaver() override;

        /// @brief Save events to the local file
        /// @param events The events content to save
        /// @return true if the events were saved successfully, false otherwise
        bool SaveEvents(const std::string& events) override;

        /// @brief Check if event saving is enabled
        /// @return true if event saving is enabled, false otherwise
        bool IsEnabled() const override;

    private:
        /// @brief Whether event saving is enabled
        bool m_enabled;

        /// @brief The path to the file where events are saved
        std::filesystem::path m_filePath;

        /// @brief Mutex to protect file writes
        mutable std::mutex m_mutex;

        /// @brief Output file stream for writing events
        std::ofstream m_outputFile;
    };
} // namespace event_saver
