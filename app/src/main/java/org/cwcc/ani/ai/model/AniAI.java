package org.cwcc.ani.ai.model;

import android.annotation.SuppressLint;
import android.content.Context;
import android.content.res.AssetManager;
import android.util.Log;

import androidx.annotation.Keep;
import androidx.annotation.NonNull;
import androidx.annotation.UiThread;

import org.cwcc.ani.ai.utils.LibraryLoader;
import org.cwcc.ani.ai.utils.ThreadUtils;

/**
 * 模型调用
 */
@UiThread
@SuppressLint("StaticFieldLeak")
@Keep
public final class AniAI {
    static {
        LibraryLoader.load();
    }
    private static final String TAG = "AniAI-AniAI";

    private static AniAI INSTANCE;

    private Context context;

    AniAI(@NonNull Context context) {
        this.context = context;
    }
    /**
     * 获取实例
     * @param context
     * @return
     */
    public static synchronized AniAI getInstance(@NonNull Context context)
    {
        ThreadUtils.init(context);
        ThreadUtils.checkThread(TAG);
        if (INSTANCE == null) {
            //Timber.plant();
            Context appContext = context.getApplicationContext();
            INSTANCE = new AniAI(appContext);
        }
        Log.i(TAG,"AniAI inited success!");
        return INSTANCE;
    }

    public static Context getApplicationContext()
    {
        if(INSTANCE==null)return null;
        return INSTANCE.context;
    }
    public static boolean hasInstance() {
        return INSTANCE != null;
    }
    /**
     *
     * @return
     */
    private static AssetManager getAssetManager(){
        Context ctx = getApplicationContext();
        if(ctx==null)return null;
        return ctx.getResources().getAssets();
    }
}
