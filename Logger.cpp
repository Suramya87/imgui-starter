#include "Logger.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

void Logger::Log(LogLevel level, const std::string& category, const std::string& message) {
    LogEntry entry;
    entry.level = level;
    entry.category = category;
    entry.message = message;

    //Time stamps 
    using namespace std::chrono;

    auto now = system_clock::now();
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    std::time_t tt = system_clock::to_time_t(now);
    std::tm local{};
#ifdef _WIN32
    localtime_s(&local, &tt);
#else
    local = *std::localtime(&tt);
#endif

    std::ostringstream oss;
    oss << std::put_time(&local, "%H:%M:%S")
        << "." << std::setfill('0') << std::setw(3) << ms.count();

    entry.time = oss.str();

    logs.push_back(entry);

    if (file.is_open()) {
        file << "[" << entry.time << "] "
             << "[" << LogLevelToString(level) << "] "
             << "[" << category << "] "
             << message << "\n";
    }
}

void Logger::Clear() {
    logs.clear();
}

// Handling the levels 
const char* Logger::LogLevelToString(LogLevel level) const {
    switch (level) {
        case LogLevel::INFO:  return "INFO";
        case LogLevel::WARN:  return "WARN";
        case LogLevel::ERROR: return "ERROR";
        default:              return "UNKNOWN";
    }
}

ImVec4 Logger::LogLevelToColor(LogLevel level) const {
    switch (level) {
        case LogLevel::INFO:  return ImVec4(1, 1, 1, 1);
        case LogLevel::WARN:  return ImVec4(1, 1, 0, 1);
        case LogLevel::ERROR: return ImVec4(1, 0.2f, 0.2f, 1);
        default:              return ImVec4(1, 1, 1, 1);
    }
}

void Logger::Draw(const char* title, bool* p_open) {
    ImGui::Begin(title, p_open);

    if (ImGui::Button("Clear")) Clear();
    ImGui::SameLine();

    if (!isFileLogging) {
        if (ImGui::Button("Start File Log")) {
            StartFileLogging("game_log.txt");
        }
    } else {
        if (ImGui::Button("Stop File Log")) {
            StopFileLogging();
        }
    }

    ImGui::Separator();

    // Input text box
    ImGui::PushItemWidth(-1);

    if (ImGui::InputText("##ConsoleInput", inputBuffer, IM_ARRAYSIZE(inputBuffer),
        ImGuiInputTextFlags_EnterReturnsTrue)) {

        if (strlen(inputBuffer) > 0) {
            Log(LogLevel::INFO, "Console", inputBuffer);
            inputBuffer[0] = '\0'; // clear input
        }
    }

    ImGui::PopItemWidth();

    ImGui::BeginChild("LogRegion", ImVec2(0, 0), true);

    for (auto& entry : logs) {
        ImGui::PushStyleColor(ImGuiCol_Text, LogLevelToColor(entry.level));

        ImGui::Text("[%s] [%s] [%s] %s",
            entry.time.c_str(),
            LogLevelToString(entry.level),
            entry.category.c_str(),
            entry.message.c_str()
        );

        ImGui::PopStyleColor();
    }

    // Auto-scroll
    if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        ImGui::SetScrollHereY(1.0f);

    ImGui::EndChild();
    ImGui::End();
}

//Record button
void Logger::StartFileLogging(const std::string& filename) {
    if (!file.is_open()) {
        file.open(filename, std::ios::out);
        isFileLogging = file.is_open();
    }
}

void Logger::StopFileLogging() {
    if (file.is_open()) {
        file.close();
    }
    isFileLogging = false;
}
