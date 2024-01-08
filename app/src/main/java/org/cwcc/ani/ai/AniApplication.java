package org.cwcc.ani.ai;

import android.app.Application;
import android.os.StrictMode;

public class AniApplication extends Application {
    @Override
    public void onCreate() {
        super.onCreate();
        StrictMode.VmPolicy policy = new StrictMode.VmPolicy.Builder()
                .detectAll()
                .penaltyLog()
                .detectFileUriExposure()
                .build();
        StrictMode.setVmPolicy(policy);
    }
}
