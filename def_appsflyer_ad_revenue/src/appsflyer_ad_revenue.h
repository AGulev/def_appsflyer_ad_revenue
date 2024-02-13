#if defined(DM_PLATFORM_ANDROID) || defined(DM_PLATFORM_IOS)

#pragma once

#include <dmsdk/sdk.h>

namespace dmAppsflyerAdRevenue
{
    static const char* MN_IRONSOURCE = "ironsource";
    static const char* MN_APPLOVINMAX = "applovinmax";
    static const char* MN_GOOGLEADMOB = "googleadmob";
    static const char* MN_FYBER = "fyber";
    static const char* MN_APPODEAL = "appodeal";
    static const char* MN_ADMOST = "Admost";
    static const char* MN_TOPON = "Topon";
    static const char* MN_TRADPLUS = "Tradplus";
    static const char* MN_YANDEX = "Yandex";
    static const char* MN_CHARTBOOST = "chartboost";
    static const char* MN_UNITY = "Unity";
    static const char* MN_CUSTOMMEDIATION = "customMediation";
    static const char* MN_DIRECT_MONETIZATION = "directMonetizationNetwork";

    static const char* PROP_COUNTRY = "country";
    static const char* PROP_AD_UNIT = "ad_unit";
    static const char* PROP_AD_TYPE = "ad_type";
    static const char* PROP_PLACEMENT = "placement";
    static const char* PROP_ECPM_PAYLOAD = "ecpm_payload";

    static const char* AD_TYPE_BANNER = "BANNER";
    static const char* AD_TYPE_INTERSTITIAL = "INTERSTITIAL";
    static const char* AD_TYPE_NATIVE = "NATIVE";
    static const char* AD_TYPE_REWARDED = "REWARDED";
    static const char* AD_TYPE_APP_OPEN = "APP_OPEN";

    void Initialize_Ext();
    void Initialize();

    void OpenEvent();
    void AddParamString(const char* param_name, const char* param);
    void SendEvent(const char* monetization_network, const char* mediation_network, const char* event_revenue_currency, double event_revenue);
    void CloseEvent();

} // namespace

#endif // platform