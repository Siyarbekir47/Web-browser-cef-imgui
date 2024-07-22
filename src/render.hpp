#pragma once

#include <cstdint>
#include <string_view>
#include <vector>

class WindowClass
{
public:
    void Draw(std::string_view label);

private:
    std::string current_url;
    std::vector<std::string> history;
    size_t history_index = 0;

    void Navigate(const std::string &url);
    void GoBack();
    void GoForward();
    void Refresh();
    bool ValidateUrl(const std::string &url);
};


void render(WindowClass &window_obj);
