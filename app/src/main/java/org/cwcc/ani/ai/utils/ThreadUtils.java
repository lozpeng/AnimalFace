package org.cwcc.ani.ai.utils;

import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.os.Looper;

import androidx.annotation.NonNull;

import org.cwcc.ani.ai.exceptions.CalledFromWorkerThreadException;

public class ThreadUtils {

    private static Boolean debug;

    /**
     * Initialises the thread utils, verifies debug state of the consuming app.
     *
     * @param context Context hosting the MapLibre Maps SDK for Android
     * @return this
     */
    public static ThreadUtils init(@NonNull Context context) {
        debug = (0 != (context.getApplicationInfo().flags & ApplicationInfo.FLAG_DEBUGGABLE));
        return null;
    }

    /**
     * Validates if execution is running on the main thread.
     *
     * @param origin  the origin of the execution
     */
    public static void checkThread(@NonNull String origin) {
        if (debug == null) {
            throw new IllegalStateException("ThreadUtils isn't correctly initialised");
        }

        if (debug) {
            if (Looper.myLooper() != Looper.getMainLooper()) {
                throw new CalledFromWorkerThreadException(
                        String.format("%s interactions should happen on the UI thread.", origin)
                );
            }
        }
    }
}
