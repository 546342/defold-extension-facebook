#if defined(DM_PLATFORM_ANDROID)

#include <dmsdk/dlib/android.h>

#include "facebook.h"

namespace dmFacebook {

struct Facebook
{
    jobject         m_FacebookJNI;
    jmethodID       m_StartSDK;
    jmethodID       m_SetAutoLogAppEventsEnabled;
    jmethodID       m_SetIsDebugEnabled;
};

static Facebook g_facebook;

static void InitJNIMethods(JNIEnv* env, jclass cls)
{
    g_facebook.m_StartSDK = env->GetMethodID(cls, "startSDK", "()V");
    g_facebook.m_SetAutoLogAppEventsEnabled = env->GetMethodID(cls, "setAutoLogAppEventsEnabled", "(Z)V");
    g_facebook.m_SetIsDebugEnabled = env->GetMethodID(cls, "setIsDebugEnabled", "(Z)V");
}

void Initialize_Ext()
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();
    jclass cls = dmAndroid::LoadClass(env, "com.defold.facebook.FacebookJNI");
    InitJNIMethods(env, cls);
    jmethodID jni_constructor = env->GetMethodID(cls, "<init>", "(Landroid/app/Activity;)V");
    g_facebook.m_FacebookJNI = env->NewGlobalRef(env->NewObject(cls, jni_constructor, threadAttacher.GetActivity()->clazz));
}

void StartSDK()
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();
    env->CallVoidMethod(g_facebook.m_FacebookJNI, g_facebook.m_StartSDK);
}

void SetAutoLogAppEventsEnabled(bool is_enabled)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();
    env->CallVoidMethod(g_facebook.m_FacebookJNI, g_facebook.m_SetAutoLogAppEventsEnabled, is_enabled);
}

void SetIsDebugEnabled(bool is_enabled)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();
    env->CallVoidMethod(g_facebook.m_FacebookJNI, g_facebook.m_SetIsDebugEnabled, is_enabled);
}

} // namespace

#endif // platform
