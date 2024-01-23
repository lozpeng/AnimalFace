package org.cwcc.ani.ai.model;

import android.content.Context;
import android.content.res.AssetManager;
import android.graphics.Bitmap;

import androidx.annotation.Keep;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import org.cwcc.ani.ai.utils.LibraryLoader;
import org.cwcc.ani.ai.utils.ThreadUtils;

/**
 * 模型调用
 */
@Keep
public final class YoloModel {
    private static YoloModel INSTANCE;

    private Context context;

    static {
        LibraryLoader.load();
    }
    private static final String TAG = "AniAI-YoloModel";

    YoloModel(@NonNull Context context) {
        this.context = context;
    }
    @Keep
    private long nativePtr;
    protected YoloModel(long nativePtr)
    {
        this.nativePtr = nativePtr;
    }
    public YoloModel() {
        checkThread();
    }
    protected void checkThread() {
        ThreadUtils.checkThread(TAG);
    }

    /**
     * 获取实例
     * @param context
     * @return
     */
    public static synchronized YoloModel getInstance(@NonNull Context context)
    {
        ThreadUtils.init(context);
        ThreadUtils.checkThread(TAG);
        if (INSTANCE == null) {
            Context appContext = context.getApplicationContext();
            INSTANCE = new YoloModel(appContext);
        }
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

    /**
     * 加载模型
     * @param modelInfo
     * @return
     */
    @Keep
    public native static boolean nativeLoadModel(ModelInfo modelInfo);

    /**
     * 检测，在检测之前需要加载模型
     * @param bitmap
     * @return
     */
    @Keep
    public native static ModelResult[] nativeDectect(Bitmap bitmap);

    /**
     * 根据模型进行检测
     * @param modelInfo
     * @param bitmap
     * @return
     */
    @Keep
    public native static boolean nativeDectectByModel(ModelInfo modelInfo, Bitmap bitmap);
}
