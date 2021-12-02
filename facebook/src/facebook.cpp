#define EXTENSION_NAME FacebookExt
#define LIB_NAME "Facebook"
#define MODULE_NAME "facebook"

#define DLIB_LOG_DOMAIN LIB_NAME

#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_ANDROID)

#include <stdlib.h>
#include "facebook.h"
#include "utils/lua_util.h"

namespace dmFacebook {

static int Lua_StartSDK(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    StartSDK();
    return 0;
}


static int Lua_SetAutoLogAppEventsEnabled(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    bool is_enabled = luaL_checkbool(L, 1);
    SetAutoLogAppEventsEnabled(is_enabled);
    return 0;
}

static int Lua_SetIsDebugEnabled(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    bool is_enabled = luaL_checkbool(L, 1);
    SetIsDebugEnabled(is_enabled);
    return 0;
}

static const luaL_reg Module_methods[] =
{
    {"start_sdk", Lua_StartSDK},
    {"set_auto_log_enabled", Lua_SetAutoLogAppEventsEnabled},
    {"set_is_debug_enabled", Lua_SetIsDebugEnabled},
    {0, 0}
};

static void LuaInit(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    luaL_register(L, MODULE_NAME, Module_methods);
    lua_pop(L, 1);
}

static dmExtension::Result AppInitializeFacebook(dmExtension::AppParams* params)
{
    Initialize_Ext();

    int isDebug = dmConfigFile::GetInt(params->m_ConfigFile, "facebook.is_debug", 0);
    if (isDebug > 0)
    {
        SetIsDebugEnabled(true);
    }

    return dmExtension::RESULT_OK;
}

static dmExtension::Result InitializeFacebook(dmExtension::Params* params)
{
    LuaInit(params->m_L);
    dmLogInfo("Registered extension Facebook");
    return dmExtension::RESULT_OK;
}

static dmExtension::Result UpdateFacebook(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

static dmExtension::Result AppFinalizeFacebook(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeFacebook(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

} // namespace

DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, dmFacebook::AppInitializeFacebook, dmFacebook::AppFinalizeFacebook, dmFacebook::InitializeFacebook, dmFacebook::UpdateFacebook,  0, dmFacebook::FinalizeFacebook)

#else // platform

static dmExtension::Result InitializeFacebook(dmExtension::Params *params) {
    dmLogInfo("Registered extension Facebook (null)");
    return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeFacebook(dmExtension::Params *params) {
    return dmExtension::RESULT_OK;
}

DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, 0, 0, InitializeFacebook, 0, 0, FinalizeFacebook)

#endif // platform