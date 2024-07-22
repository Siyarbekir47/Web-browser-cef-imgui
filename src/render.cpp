#include <iostream>
#include <regex>

#include <fmt/format.h>
#include <imgui.h>
#include <implot.h>

#include "render.hpp"

void WindowClass::Draw(std::string_view label)
{
  constexpr static auto window_flags =
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(1280, 720));

    ImGui::Begin(label.data(), nullptr, window_flags);

    //add URL bar
    static char url[256] = "";
    ImGui::Text("URL");
    ImGui::SameLine();
    ImGui::InputText("##URL", url, IM_ARRAYSIZE(url));
    ImGui::SameLine();
    if (ImGui::Button("Go")){
        Navigate(url);
    }
    ImGui::SameLine();
    if(    ImGui::ArrowButton("##Back", ImGuiDir_Left)){
        GoBack();
    }

    ImGui::SameLine();
    if(    ImGui::ArrowButton("##Forward", ImGuiDir_Right)){
        GoForward();
    }

    ImGui::SameLine();
    if (ImGui::Button("Refresh")){
        Refresh();
    }
    ImGui::Separator();

    //add browser content
    ImGui::BeginChild("Content", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()),true);
    ImGui::Text("Current URL: %s", current_url.c_str());
    ImGui::EndChild();

    ImGui::End();
}

void WindowClass::Navigate(const std::string& url)
{
    if(ValidateUrl(url)){

        if(history_index < history.size() -1){
            history.erase(history.begin() + history_index + 1, history.end());
        }
        current_url = url;
        history.push_back(url);
        history_index = history.size() - 1;

        std::cout << "Navigating to: " << url << std::endl;


        }
        else
        {
            std::cerr << "Invalid URL: " << url << std::endl;
        }

    }

void WindowClass::GoBack()
{
    if (history_index > 0)
    {
        history_index--;
        current_url = history[history_index];
        std::cout << "Going back to: " << current_url << std::endl;
    }
}

void WindowClass::GoForward()
{
    if (history_index < history.size() - 1)
    {
        history_index++;
        current_url = history[history_index];
        std::cout << "Going forward to: " << current_url << std::endl;
    }
}

void WindowClass::Refresh()
{
    std::cout << "Refreshing current page: " << current_url << std::endl;
}

bool WindowClass::ValidateUrl(const std::string& url)
{
    // This is a basic URL validation, you might want to improve it
    std::regex url_regex(R"(^(http|https):\/\/[\w\-_]+(\.[\w\-_]+)+([\w\-\.,@?^=%&amp;:/~\+#]*[\w\-\@?^=%&amp;/~\+#])?$)");
    return std::regex_match(url, url_regex);
}

void render(WindowClass &window_obj)
{
    window_obj.Draw("Tab: 1");
}
