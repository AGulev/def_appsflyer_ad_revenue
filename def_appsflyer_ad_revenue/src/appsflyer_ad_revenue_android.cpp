#if defined(DM_PLATFORM_ANDROID)

#include <dmsdk/dlib/android.h>

#include "appsflyer_ad_revenue.h"

namespace dmAppsflyerAdRevenue {

struct AdRevenue
{
    jobject         m_AdRevenueJNI;
    jmethodID       m_Initialize;
    jmethodID       m_LogAdRevenue;

    jmethodID      m_OpenEvent;
    jmethodID      m_AddParamNumber;
    jmethodID      m_AddParamString;
    jmethodID      m_SendEvent;
    jmethodID      m_CloseEvent;
};

static AdRevenue g_AdRevenue;

static void InitJNIMethods(JNIEnv* env, jclass cls)
{
    g_AdRevenue.m_Initialize =      env->GetMethodID(cls, "Initialize", "()V");

    g_AdRevenue.m_OpenEvent =       env->GetMethodID(cls, "openEvent", "()V");
    g_AdRevenue.m_AddParamString =  env->GetMethodID(cls, "addParamString", "(Ljava/lang/String;Ljava/lang/String;)V");
    g_AdRevenue.m_SendEvent =       env->GetMethodID(cls, "sendEvent", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;D)V");
    g_AdRevenue.m_CloseEvent =      env->GetMethodID(cls, "closeEvent", "()V");
}

void Initialize_Ext()
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();
    jclass cls = dmAndroid::LoadClass(env, "com.defold.hgpoint.AppsflyerAdRevenueJNI");
    InitJNIMethods(env, cls);
    jmethodID jni_constructor = env->GetMethodID(cls, "<init>", "(Landroid/app/Activity;)V");
    g_AdRevenue.m_AdRevenueJNI = env->NewGlobalRef(env->NewObject(cls, jni_constructor, threadAttacher.GetActivity()->clazz));
}

void Initialize()
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();
    env->CallVoidMethod(g_AdRevenue.m_AdRevenueJNI, g_AdRevenue.m_Initialize);
}

dmAndroid::ThreadAttacher* g_threadAttacher = 0x0;

void OpenEvent()
{
    if (g_threadAttacher != 0x0)
    {
        delete g_threadAttacher;
        g_threadAttacher = 0x0;
    }
    g_threadAttacher = new dmAndroid::ThreadAttacher();
    JNIEnv* env = g_threadAttacher->GetEnv();
    env->CallVoidMethod(g_AdRevenue.m_AdRevenueJNI, g_AdRevenue.m_OpenEvent);
}

void AddParamString(const char* param_name, const char* param)
{
    JNIEnv* env = g_threadAttacher->GetEnv();
    jstring jparam_name = env->NewStringUTF(param_name);
    jstring jparam = env->NewStringUTF(param);
    env->CallVoidMethod(g_AdRevenue.m_AdRevenueJNI , g_AdRevenue.m_AddParamString, jparam_name, jparam);
    env->DeleteLocalRef(jparam_name);
    env->DeleteLocalRef(jparam);
}

void SendEvent(const char* monetization_network, const char* mediation_network, const char* event_revenue_currency, double event_revenue)
{
    JNIEnv* env = g_threadAttacher->GetEnv();
    jstring jevent_name = env->NewStringUTF(monetization_network);
    jstring jmediation_network = env->NewStringUTF(mediation_network);
    jstring jevent_revenue_currency = env->NewStringUTF(event_revenue_currency);
    env->CallVoidMethod(g_AdRevenue.m_AdRevenueJNI, g_AdRevenue.m_SendEvent, jevent_name, jmediation_network, jevent_revenue_currency, event_revenue);
    env->DeleteLocalRef(jevent_name);
    env->DeleteLocalRef(jmediation_network);
    env->DeleteLocalRef(jevent_revenue_currency); 
}

void CloseEvent()
{
    JNIEnv* env = g_threadAttacher->GetEnv();
    env->CallVoidMethod(g_AdRevenue.m_AdRevenueJNI, g_AdRevenue.m_CloseEvent);
    delete g_threadAttacher;
    g_threadAttacher = 0x0;
}

} // namespace

#endif // platform
