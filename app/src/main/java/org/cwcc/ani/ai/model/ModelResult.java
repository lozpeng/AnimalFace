package org.cwcc.ani.ai.model;

import androidx.annotation.Keep;
import androidx.annotation.NonNull;

import org.cwcc.ani.ai.utils.LibraryLoader;
import org.cwcc.ani.ai.utils.ThreadUtils;

/**
 * 模型运行后结果，模型返回后应该是一个列表
 */
public class ModelResult {
    private static final String TAG = "AniAI-ModelResult";
    static {
        LibraryLoader.load();
    }

    @Keep
    private long nativePtr;
    protected boolean detached;

    protected ModelResult(long nativePtr)
    {
        this.nativePtr = nativePtr;
    }
    public ModelResult() {
        checkThread();
    }

    protected void checkThread() {
        ThreadUtils.checkThread(TAG);
    }

    public long getNativePtr() {
        return nativePtr;
    }

    public Float getX()
    {
        this.checkThread();
        return nativeGetX();
    }
    public Float getY()
    {
        this.checkThread();
        return nativeGetY();
    }

    public Float getW()
    {
        this.checkThread();
        return nativeGetW();
    }

    public Float getH()
    {
        this.checkThread();
        return nativeGetH();
    }

    public Float getProb()
    {
        this.checkThread();
        return nativeGetProb();
    }

    public String getLabel()
    {
        this.checkThread();
        return nativeGetLabel();
    }

    @NonNull
    @Keep
    protected native String nativeGetId();
    @NonNull
    @Keep
    protected native Float nativeGetX();

    @NonNull
    @Keep
    protected native Float nativeGetY();

    @NonNull
    @Keep
    protected native Float nativeGetW();

    @NonNull
    @Keep
    protected native Float nativeGetH();

    @NonNull
    @Keep
    protected native Float nativeGetProb();

    @NonNull
    @Keep
    protected native String nativeGetLabel();
}
