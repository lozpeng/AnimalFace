package org.cwcc.ani.ai;

import android.app.Application;
import android.os.StrictMode;

import org.cwcc.ani.ai.model.AniAI;

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
        AniAI.getInstance(getApplicationContext());
    }
}
