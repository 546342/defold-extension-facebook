package com.defold.facebook;

import android.util.Log;
import android.app.Activity;

import com.facebook.LoggingBehavior;
import com.facebook.FacebookSdk;

public class FacebookJNI {
    private static final String TAG = "FacebookJNI";

    private Activity activity;

    public FacebookJNI(Activity activity) {
        this.activity = activity;
    }

    public void startSDK() {
        Log.d(TAG, "Start SDK");
        FacebookSdk.setAutoInitEnabled(true);
        FacebookSdk.fullyInitialize();
    }

    public void setAutoLogAppEventsEnabled(boolean is_enabled) {
        Log.d(TAG, "Set auto log app events enabled: " + String.valueOf(is_enabled));
        FacebookSdk.setAutoLogAppEventsEnabled(is_enabled);
    }

    public void setIsDebugEnabled(boolean is_enabled) {
        Log.d(TAG, "Set debug log enabled: " + String.valueOf(is_enabled));
        FacebookSdk.addLoggingBehavior(LoggingBehavior.REQUESTS);
        FacebookSdk.addLoggingBehavior(LoggingBehavior.APP_EVENTS);
        FacebookSdk.addLoggingBehavior(LoggingBehavior.INCLUDE_RAW_RESPONSES);
        FacebookSdk.addLoggingBehavior(LoggingBehavior.CACHE);
        FacebookSdk.setIsDebugEnabled(is_enabled);
    }
}
