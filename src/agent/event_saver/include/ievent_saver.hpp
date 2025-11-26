#pragma once

#include <string>

namespace event_saver
{
    /// @brief Interface for saving events locally
    ///
    /// This interface defines the contract for saving events that are sent
    /// to the server. Implementations can save events to files, databases,
    /// or other storage mechanisms for later processing (e.g., syslog forwarding).
    class IEventSaver
    {
    public:
        /// @brief Virtual destructor
        virtual ~IEventSaver() = default;

        /// @brief Save events to local storage
        /// @param events The events content to save (as sent to the server)
        /// @return true if the events were saved successfully, false otherwise
        virtual bool SaveEvents(const std::string& events) = 0;

        /// @brief Check if event saving is enabled
        /// @return true if event saving is enabled, false otherwise
        virtual bool IsEnabled() const = 0;
    };
} // namespace event_saver
