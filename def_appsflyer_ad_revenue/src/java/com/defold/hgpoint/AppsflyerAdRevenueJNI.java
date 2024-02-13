package com.defold.hgpoint;

import android.util.Log;
import android.app.Activity;
import android.app.Application;

import com.appsflyer.adrevenue.adnetworks.AppsFlyerAdNetworkEventType;
import com.appsflyer.adrevenue.adnetworks.generic.MediationNetwork;
import com.appsflyer.adrevenue.adnetworks.generic.Scheme;
import com.appsflyer.adrevenue.AppsFlyerAdRevenue;

import java.util.Currency;
import java.util.HashMap;
import java.util.Map;
import java.util.Locale;

public class AppsflyerAdRevenueJNI {
    private static final String TAG = "AppsflyerAdRevenue";

    private Activity activity;
    private Application application;

    public AppsflyerAdRevenueJNI(Activity activity) {
        this.activity = activity;
        this.application = activity.getApplication();
    }

    public void Initialize() {
        AppsFlyerAdRevenue.Builder afRevenueBuilder = new AppsFlyerAdRevenue.Builder(this.application);
        AppsFlyerAdRevenue.initialize(afRevenueBuilder.build());
    }

    private Map<String, String> g_customParams;

    public void openEvent() {
        g_customParams = new HashMap<>();
    }

    public void addParamString(String param_name, String param) {
        g_customParams.put(param_name, param);
    }

    public void sendEvent(String monetizationNetwork, String mediationNetwork, String eventRevenueCurrency, double eventRevenue) {
        AppsFlyerAdRevenue.logAdRevenue(
            monetizationNetwork,
            MediationNetwork.valueOf(mediationNetwork),
            Currency.getInstance(eventRevenueCurrency),
            eventRevenue,
            g_customParams
        );
    }

    public void closeEvent() {
        g_customParams = null;
    }
}
