#include "Logger.h"

void Logger::Log(LogLevel level, const std::string& category, const std::string& message) {
    LogEntry entry;
    entry.level = level;
    entry.category = category;
    entry.message = message;
    logs.push_back(entry);
}

void Logger::Clear() {
    logs.clear();
}

const char* Logger::LogLevelToString(LogLevel level) const {
    switch(level) {
        case LogLevel::INFO: return "INFO";
        case LogLevel::WARN: return "WARN";
        case LogLevel::ERROR: return "ERROR";
    }
}

ImVec4 Logger::LogLevelToColor(LogLevel level) const {
    switch(level) {
        case LogLevel::INFO:  return ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        case LogLevel::WARN:  return ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
        case LogLevel::ERROR: return ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
        default: return ImVec4(1,1,1,1);
    }
}

void Logger::Draw(const char* title, bool* p_open) {
    ImGui::Begin(title, p_open);

    if (ImGui::Button("Clear")) Clear();
    ImGui::Separator();

    ImGui::BeginChild("LogRegion", ImVec2(0, 0), true);

    for (auto& entry : logs) {
        ImGui::PushStyleColor(ImGuiCol_Text, LogLevelToColor(entry.level));
        ImGui::Text("[%s] %s", entry.category.c_str(), entry.message.c_str());
        ImGui::PopStyleColor();
    }

    if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        ImGui::SetScrollHereY(1.0f);

    ImGui::EndChild();
    ImGui::End();
}
