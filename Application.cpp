#include "Application.h"
#include "imgui/imgui.h"
#include "Logger.h"  // your logger class

namespace ClassGame {

    // Single Logger instance for the game
    static Logger logger;

    //
    // game starting point
    //
    void GameStartUp() 
    {
        // Initialize logging system
        logger.Log(LogLevel::INFO, "SYSTEM", "Game started successfully");
        logger.Log(LogLevel::INFO, "SYSTEM", "Application initialized");
    }

    //
    // game render loop
    //
    void RenderGame() 
    {
        // Docking space and demo window
        ImGui::DockSpaceOverViewport();
        ImGui::ShowDemoWindow();

        // --- Game-specific ImGui log demo ---
        ImGui::Begin("ImGui Log Demo");
        ImGui::LogButtons();

        if (ImGui::Button("Copy \"Hello, world!\" to clipboard"))
        {
            ImGui::LogToClipboard();
            ImGui::LogText("Hello, world!");
            ImGui::LogFinish();
        }
        ImGui::End();

        // --- Logger UI ---
        logger.Draw("Game Log");

        // --- Buttons to test logging ---
        ImGui::Begin("Logging Test Buttons");
        if (ImGui::Button("Log Game Event"))
            logger.Log(LogLevel::INFO, "GAME", "Player made a move");
        ImGui::SameLine();
        if (ImGui::Button("Log Warning"))
            logger.Log(LogLevel::WARN, "GAME", "Invalid move attempted");
        ImGui::SameLine();
        if (ImGui::Button("Log Error"))
            logger.Log(LogLevel::ERROR, "GAME", "Game state corrupted");
        ImGui::End();
    }

    //
    // end turn is called by the game code at the end of each turn
    //
    void EndOfTurn() 
    {
        // Example: log end of turn
        logger.Log(LogLevel::INFO, "GAME", "Turn ended");
    }

} // namespace ClassGame
