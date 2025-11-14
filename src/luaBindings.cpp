#include "lua.hpp"
#include "imgui.h"
#include <iostream>

lua_State* InitLua()
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    return L;
}

static int lua_ImGui_Text(lua_State* L)
{
    const char* text = luaL_checkstring(L, 1);
    ImGui::Text("%s", text);
    return 0;
}

void RegisterImGuiToLua(lua_State* L)
{
    lua_newtable(L);
    lua_pushcfunction(L, lua_ImGui_Text);
    lua_setfield(L, -2, "Text");
    lua_setglobal(L, "ImGui");
}
