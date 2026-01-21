#include "Application.h"
#include "imgui/imgui.h"
#include "Logger.h"

namespace ClassGame {
        //
        // our global variables
        //
        static Logger logger;

        //
        // game starting point
        // this is called by the main render loop in main.cpp
        //
        void GameStartUp() 
        {
            // Initialize logging system
//            Logger& logger = Logger::GetInstance();
//            logger.LogInfo("Game started successfully");
//            logger.LogGameEvent("Application initialized");
            logger.Log(LogLevel::INFO, "SYSTEM", "Game started successfully");
            logger.Log(LogLevel::INFO, "SYSTEM", "Application initialized");
        }

        //
        // game render loop
        // this is called by the main render loop in main.cpp
        //
        void RenderGame() 
        {
            ImGui::DockSpaceOverViewport();
            ImGui::ShowDemoWindow();

            ImGui::Begin("ImGui Log Demo");
            ImGui::LogButtons();

            if (ImGui::Button("Copy \"Hello, world!\" to clipboard"))
            {
                ImGui::LogToClipboard();
                ImGui::LogText("Hello, world!");
                ImGui::LogFinish();
            }
            ImGui::End();

        

        logger.Draw("Game Log");

        ImGui::Begin("Logging Test Buttons");
        if (ImGui::Button("Log Game Event"))
            logger.Log(LogLevel::INFO, "GAME", "Player made a move");
        ImGui::SameLine();
        if (ImGui::Button("Log Warning"))
            logger.Log(LogLevel::WARN, "GAME", "Invalid move attempted");
        ImGui::SameLine();
        if (ImGui::Button("Log Error"))
            logger.Log(LogLevel::ERROR, "GAME", "Game state corrupted");
        // ImGui::SameLine();
        // ImGui::TextColored(
        //     isFileLogging ? ImVec4(0,1,0,1) : ImVec4(1,0,0,1),
        //     isFileLogging ? "Recording" : "Not Recording"
        // );

        ImGui::End();
        }

        //
        // end turn is called by the game code at the end of each turn
        // this is where we check for a winner
        //
        void EndOfTurn() 
        {
        }
}
