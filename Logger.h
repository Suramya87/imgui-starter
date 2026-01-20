#pragma once
#include "imgui/imgui.h"  
#include <string>
#include <vector>

enum class LogLevel { INFO, WARN, ERROR };

struct LogEntry {
    LogLevel level;
    std::string category;
    std::string message;
};

class Logger {
public:
    void Log(LogLevel level, const std::string& category, const std::string& message);
    void Clear();
    void Draw(const char* title, bool* p_open = nullptr); // Draw ImGui window

private:
    std::vector<LogEntry> logs;

    const char* LogLevelToString(LogLevel level) const;
    ImVec4 LogLevelToColor(LogLevel level) const;
};
