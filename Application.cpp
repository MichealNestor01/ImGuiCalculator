#include "Application.h"

#include "Calculator.h"
#include "imgui.h"
#include <string>

namespace MyApp {
    ImVec2 genericButtonSize = ImVec2(190, 114);
    ImVec2 longButtonSize = ImVec2(388, 114);

    void RenderUI() {
        static bool use_work_area = true;
        static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;

        // We demonstrate using the full viewport area or the work area (without menu-bars, task-bars etc.)
        // Based on your use case you may want one of the other.
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
        ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);

        if (ImGui::Begin("Calculator", nullptr, flags))
        {
            static Calculator calculator = Calculator();

            std::string calc_output = calculator.getStack();
            ImGui::Text(calc_output.c_str());
            
            for (int num = 1; num <= 9; num++) {
                if ((num-1)%3 != 0) ImGui::SameLine();
                std::string button_text = std::to_string(num);
                if (ImGui::Button(button_text.c_str(), genericButtonSize)) {
                    calculator.addToStack(num);
                }
            }
            ImGui::PushID(0);
            ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.0f, 0.81f, 0.99f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.0f, 0.54f, 0.99f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.0f, 0.34f, 0.99f));
            if (ImGui::Button("+", genericButtonSize)) {
                calculator.addToStack(ADD);
            }
            ImGui::PopStyleColor(3);
            ImGui::PopID();
            ImGui::SameLine();
            std::string button_text = std::to_string(0);
            if (ImGui::Button(button_text.c_str(), genericButtonSize)) {
                calculator.addToStack(0);
            }
            //hsv(354, 81%, 99%)
            ImGui::PushID(0);
            ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.0f, 0.81f, 0.99f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.0f, 0.54f, 0.99f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.0f, 0.34f, 0.99f));
            ImGui::SameLine();
            if (ImGui::Button("-", genericButtonSize)) {
                calculator.addToStack(SUB);
            }

            if (ImGui::Button("/", genericButtonSize)) {
                calculator.addToStack(DIV);
            }
            ImGui::SameLine();
            if (ImGui::Button("x", genericButtonSize)) {
                calculator.addToStack(MUL);
            }
            ImGui::SameLine();
            if (ImGui::Button("=", genericButtonSize)) {
                int answer = calculator.eval();
                calculator.clear();
                calculator.addToStack(answer);
            }
            ImGui::PopStyleColor(3);
            ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.8f, 0.81f, 0.99f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.8f, 0.54f, 0.99f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.8f, 0.34f, 0.99f));
            if (ImGui::Button("DEL", longButtonSize)) {
                calculator.undo();
            }
            ImGui::SameLine();
            if (ImGui::Button("C", genericButtonSize)) {
                calculator.clear();
            }
            ImGui::PopStyleColor(3);
            ImGui::PopID();
        }
        ImGui::End();
    }
}
