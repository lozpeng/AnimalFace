package org.cwcc.ani.ai.model;

import android.content.res.AssetManager;
import android.graphics.Bitmap;

import androidx.annotation.Keep;

import org.cwcc.ani.ai.utils.LibraryLoader;
import org.cwcc.ani.ai.utils.ThreadUtils;

/**
 * 模型调用
 */
public class YoloModel {
    static {
        LibraryLoader.load();
    }
    private static final String TAG = "AniAI-YoloModel";
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
     * 加载模型
     * @param modelInfo
     * @return
     */
    @Keep
    public native boolean nativeLoadModel(ModelInfo modelInfo);

    /**
     * 检测，在检测之前需要加载模型
     * @param bitmap
     * @return
     */
    @Keep
    public native ModelResult[] nativeDectect(Bitmap bitmap);

    /**
     * 根据模型进行检测
     * @param modelInfo
     * @param bitmap
     * @return
     */
    @Keep
    public native boolean nativeDectectByModel(ModelInfo modelInfo, Bitmap bitmap);


}
