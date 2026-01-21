#pragma once
#include "imgui/imgui.h"  
#include <string>
#include <vector>
#include <fstream>
#include <ctime>


enum class LogLevel { INFO, WARN, ERROR };

struct LogEntry {
    LogLevel level;
    std::string category;
    std::string message;
    std::string time;
};

class Logger {
public:
    void Log(LogLevel level, const std::string& category, const std::string& message);
    void Clear();
    void Draw(const char* title, bool* p_open = nullptr); // Draw ImGui window
    void StartFileLogging(const std::string& filename);
    void StopFileLogging();
    // bool isFileLogging = false;

private:
    std::vector<LogEntry> logs;
    std::ofstream file;

    const char* LogLevelToString(LogLevel level) const;
    ImVec4 LogLevelToColor(LogLevel level) const;
    bool isFileLogging = false;
    char inputBuffer[256] = {};



};
