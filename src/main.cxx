#include <iostream>
#include <iterator>

#include "vulkan/vulkan.hpp"

namespace GLFW {
    #include "GLFW/glfw3.h"
}

#include "lua.hpp"

int API_closeWindow(lua_State *L) {
    using namespace GLFW;

    GLFWwindow *w = (GLFWwindow*) lua_topointer(L, 1);

    glfwDestroyWindow(w);

    return 0;
}

int API_createWindow(lua_State *L) {
    using namespace GLFW;

    double X = lua_tonumber(L, 1);  /* get argument */
    double Y = lua_tonumber(L, 2);  /* get argument */
    const char* name = lua_tostring(L, 3);  /* get argument */

    GLFWwindow *w = glfwCreateWindow((int)X, (int)Y, name, NULL, NULL);

    lua_pushlightuserdata(L, (void*) w);

    return 1;
}

int API_shouldWindowClose(lua_State *L)
{
    using namespace GLFW;

    GLFWwindow *w = (GLFWwindow*) lua_topointer(L, 1);

    if (glfwWindowShouldClose(w)) {
        lua_pushboolean(L, true);
    }else{
        lua_pushboolean(L, false);
    }

    return 1;
}

int API_swapBuffers(lua_State *L)
{
    using namespace GLFW;

    GLFWwindow *w = (GLFWwindow*) lua_topointer(L, 1);
    glfwSwapBuffers(w);

    return 0;
}

int API_pollEvents(lua_State *L)
{
    GLFW::glfwPollEvents();
    return 0;
}

int main(void)
{

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    GLFW::glfwInit();

    lua_pushcfunction(L, API_createWindow);
    lua_setglobal(L, "createWindow");

    lua_pushcfunction(L, API_shouldWindowClose);
    lua_setglobal(L, "windowShouldClose");

    lua_pushcfunction(L, API_closeWindow);
    lua_setglobal(L, "closeWindow");

    lua_pushcfunction(L, API_swapBuffers);
    lua_setglobal(L, "swapBuffers");

    lua_pushcfunction(L, API_pollEvents);
    lua_setglobal(L, "pollEvents");


    using namespace GLFW;
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    luaL_dofile(L, "scripts/main.lua");

    lua_close(L);

    return 0;
}