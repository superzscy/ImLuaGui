#define SOL_ALL_SAFETIES_ON 1
#include "imgui.h"
#include "sol.hpp"

namespace sol_ImGui
{
    // Widgets: Main
    inline void Text(const std::string& text)
    {
        ImGui::Text(text.c_str());
    }

    inline bool Button(const std::string& label)
    {
        return ImGui::Button(label.c_str());
    }

    inline bool Button(const std::string& label, float sizeX, float sizeY)
    {
        return ImGui::Button(label.c_str(), { sizeX, sizeY });
    }

    inline std::tuple<bool, bool> Checkbox(const std::string& label, bool v)
    {
        bool value{ v };
        bool pressed = ImGui::Checkbox(label.c_str(), &value);

        return std::make_tuple(value, pressed);
    }

    inline std::tuple<std::string, bool> InputText(const std::string& label, std::string text, unsigned int bufSize) 
    { 
        std::vector<char> buf(bufSize);
        strncpy_s(buf.data(), bufSize, text.c_str(), bufSize - 1);
        buf[bufSize - 1] = '\0';
        bool value_changed = ImGui::InputText(label.c_str(), buf.data(), bufSize);
        return { std::string(buf.data()), value_changed };
    }

    inline std::tuple<std::string, bool> InputText(const std::string& label, std::string text, unsigned int bufSize, int flags)
    {
        std::vector<char> buf(bufSize);
        strncpy_s(buf.data(), bufSize, text.c_str(), bufSize - 1);
        buf[bufSize - 1] = '\0';
        bool value_changed = ImGui::InputText(label.c_str(), buf.data(), bufSize, static_cast<ImGuiInputTextFlags>(flags));
        return { std::string(buf.data()), value_changed };
    }

    inline std::tuple<int, bool> ListBox(const std::string& label, int currentItem, const sol::table& items, int itemCount)
    {
        std::vector<std::string> strings;
        for (int i = 1; i <= itemCount; i++)
        {
            const auto& stringItem = items.get<sol::optional<std::string>>(i);
            strings.push_back(stringItem.value_or("Missing"));
        }

        std::vector<const char*> cstrings;
        for (auto& string : strings)
        {
            cstrings.push_back(string.c_str());
        }

        currentItem -= 1; // lua start from 1

        bool clicked = ImGui::ListBox(label.c_str(), &currentItem, cstrings.data(), itemCount);
        return std::make_tuple(currentItem + 1, clicked);
    }

    // Cursor / Layout
    inline void Separator() { ImGui::Separator(); }
    inline void SameLine() { ImGui::SameLine(); }
    inline void SameLine(float offsetFromStartX) { ImGui::SameLine(offsetFromStartX); }
    inline void SameLine(float offsetFromStartX, float spacing) { ImGui::SameLine(offsetFromStartX, spacing); }

    void Init(sol::state& lua)
    {
        sol::table ImGui = lua.create_named_table("ImGui");

#pragma region Widgets: Main
        ImGui.set_function("Text", Text);

        ImGui.set_function("Button", sol::overload(
            sol::resolve<bool(const std::string&)>(Button),
            sol::resolve<bool(const std::string&, float, float)>(Button)
        ));

        ImGui.set_function("Checkbox", Checkbox);

        ImGui.set_function("InputText", sol::overload(
                sol::resolve<std::tuple<std::string, bool>(const std::string&, std::string, unsigned int)>(InputText),
                sol::resolve<std::tuple<std::string, bool>(const std::string&, std::string, unsigned int, int)>(InputText)
            ));
#pragma endregion Widgets: Main

#pragma region Widgets: List Boxes
        ImGui.set_function("ListBox", sol::overload(
            sol::resolve<std::tuple<int, bool>(const std::string&, int, const sol::table&, int)>(ListBox)
        ));
#pragma endregion Widgets: List Boxes

#pragma region Cursor / Layout
        ImGui.set_function("Separator", Separator);
        ImGui.set_function("SameLine", sol::overload(
            sol::resolve<void()>(SameLine),
            sol::resolve<void(float)>(SameLine)
            ));
#pragma endregion Cursor / Layout
    }
}