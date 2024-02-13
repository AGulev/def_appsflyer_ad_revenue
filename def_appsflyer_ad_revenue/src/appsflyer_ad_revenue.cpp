#define EXTENSION_NAME AppsflyerAdRevenueExt
#define LIB_NAME "AppsflyerAdRevenue"
#define MODULE_NAME "appsflyer_ad_revenue"

#define DLIB_LOG_DOMAIN LIB_NAME

#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_ANDROID) || defined(DM_PLATFORM_IOS)

#include <stdlib.h>
#include "appsflyer_ad_revenue.h"
#include "utils/lua_util.h"

namespace dmAppsflyerAdRevenue
{

    static int Lua_Initialize(lua_State *L)
    {
        DM_LUA_STACK_CHECK(L, 0);
        Initialize();
        return 0;
    }

    static int Lua_LogAdRevenue(lua_State *L)
    {
        DM_LUA_STACK_CHECK(L, 0);

        const char* monetization_network = luaL_checkstring(L, 1);
        const char* mediation_network = luaL_checkstring(L, 2);
        const char* event_revenue_currency = luaL_checkstring(L, 3);
        double event_revenue = luaL_checknumber(L, 4);

        luaL_checktype(L, 5, LUA_TTABLE);
        OpenEvent();
        lua_pushvalue(L, 5);
        lua_pushnil(L);
        while (lua_next(L, -2) != 0)
        {
            const char* param_name = lua_tostring(L, -2);
            const char* param_value = luaL_checkstring(L, -1);
            AddParamString(param_name, param_value);
            lua_pop(L, 1);
        }

        SendEvent(monetization_network, mediation_network, event_revenue_currency, event_revenue);
        CloseEvent();
        lua_pop(L, 1);
        
        return 0;
    }

    static const luaL_reg Module_methods[] =
        {
            {"initialize", Lua_Initialize},
            {"log_ad_revenue", Lua_LogAdRevenue},
            {0, 0}};

    static void LuaInit(lua_State *L)
    {
        DM_LUA_STACK_CHECK(L, 0);
        luaL_register(L, MODULE_NAME, Module_methods);
#define SETCONSTANT(name)                \
    lua_pushstring(L, name); \
    lua_setfield(L, -2, #name);

        SETCONSTANT(MN_IRONSOURCE)
        SETCONSTANT(MN_APPLOVINMAX)
        SETCONSTANT(MN_GOOGLEADMOB)
        SETCONSTANT(MN_FYBER)
        SETCONSTANT(MN_APPODEAL)
        SETCONSTANT(MN_ADMOST)
        SETCONSTANT(MN_TOPON)
        SETCONSTANT(MN_TRADPLUS)
        SETCONSTANT(MN_YANDEX)
        SETCONSTANT(MN_CHARTBOOST)
        SETCONSTANT(MN_UNITY)
        SETCONSTANT(MN_CUSTOMMEDIATION)
        SETCONSTANT(MN_DIRECT_MONETIZATION)

        SETCONSTANT(PROP_COUNTRY)
        SETCONSTANT(PROP_AD_UNIT)
        SETCONSTANT(PROP_AD_TYPE)
        SETCONSTANT(PROP_PLACEMENT)
        SETCONSTANT(PROP_ECPM_PAYLOAD)

        SETCONSTANT(AD_TYPE_BANNER)
        SETCONSTANT(AD_TYPE_INTERSTITIAL)
        SETCONSTANT(AD_TYPE_NATIVE)
        SETCONSTANT(AD_TYPE_REWARDED)
        SETCONSTANT(AD_TYPE_APP_OPEN)

#undef SETCONSTANT
        lua_pop(L, 1);
    }

    static dmExtension::Result AppInitializeAppsflyerAdRevenue(dmExtension::AppParams *params)
    {
        Initialize_Ext();
        return dmExtension::RESULT_OK;
    }

    static dmExtension::Result InitializeAppsflyerAdRevenue(dmExtension::Params *params)
    {
        LuaInit(params->m_L);
        dmLogInfo("Registered extension AppsflyerAdRevenue");
        return dmExtension::RESULT_OK;
    }

    static dmExtension::Result UpdateAppsflyerAdRevenue(dmExtension::Params *params)
    {
        return dmExtension::RESULT_OK;
    }

    static dmExtension::Result AppFinalizeAppsflyerAdRevenue(dmExtension::AppParams *params)
    {
        return dmExtension::RESULT_OK;
    }

    static dmExtension::Result FinalizeAppsflyerAdRevenue(dmExtension::Params *params)
    {
        return dmExtension::RESULT_OK;
    }

} // namespace

DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, dmAppsflyerAdRevenue::AppInitializeAppsflyerAdRevenue, dmAppsflyerAdRevenue::AppFinalizeAppsflyerAdRevenue, dmAppsflyerAdRevenue::InitializeAppsflyerAdRevenue, dmAppsflyerAdRevenue::UpdateAppsflyerAdRevenue, 0, dmAppsflyerAdRevenue::FinalizeAppsflyerAdRevenue)

#else // platform

static dmExtension::Result InitializeAppsflyerAdRevenue(dmExtension::Params *params)
{
    dmLogInfo("Registered extension AppsflyerAdRevenue (null)");
    return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeAppsflyerAdRevenue(dmExtension::Params *params)
{
    return dmExtension::RESULT_OK;
}

DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, 0, 0, InitializeAppsflyerAdRevenue, 0, 0, FinalizeAppsflyerAdRevenue)

#endif // platform