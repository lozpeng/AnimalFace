package org.cwcc.ani.ai.model;

import android.os.Parcel;
import android.os.Parcelable;

import androidx.annotation.Keep;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import org.cwcc.ani.ai.utils.LibraryLoader;
import org.cwcc.ani.ai.utils.ThreadUtils;

/**
 * 模型基本信息
 */
public class ModelInfo{
    static {
        LibraryLoader.load();
    }
    private static final String TAG = "AniAI-ModelInfo";
    @Keep
    private long nativePtr;
    protected boolean detached;

    protected ModelInfo(long nativePtr)
    {
        this.nativePtr = nativePtr;
    }
    public ModelInfo() {
        checkThread();
    }

    protected void checkThread() {
        ThreadUtils.checkThread(TAG);
    }

    public long getNativePtr() {
        return nativePtr;
    }

    @Keep
    protected native void setModelId(@NonNull String modelId);

    @Keep
    protected native void setModelName(@NonNull String modelName);

    @Keep
    protected native void setInputName(@NonNull String inputName);

    @Keep
    protected native void setOutputName(@NonNull String outputName);

    @Keep
    protected native void setGPUCUP(@NonNull Boolean gpucup);

    @Keep
    protected native void setTargetSize(@NonNull Float targetSize);

    @Keep
    protected native void setClasses(@NonNull Integer classes);
    @Keep
    protected native void setMeanVals(@NonNull Float[] meanVals);

    @Keep
    protected native void setNormalVals(@NonNull Float[] normalVals);

    @NonNull
    @Keep
    protected native String getModelId();

    @NonNull
    @Keep
    protected native String getModelName();

    @NonNull
    @Keep
    protected native String getInputName();

    @NonNull
    @Keep
    protected native String getOutputName();

    @NonNull
    @Keep
    protected native Boolean getGPUCUP();

    @NonNull
    @Keep
    protected native Float getTargetSize();

    @NonNull
    @Keep
    protected native Integer getClasses();
    @NonNull
    @Keep
    protected native Float[] getMeanVals();

    @NonNull
    @Keep
    protected native Float[] getNormalVals();

    public static float[] Float2float(Float[] arr)
    {
        float[] farr = new float[arr.length];
        for (int i=0;i<arr.length;i++ ) {
            Float f = arr[i];
            if(f==null||Float.isNaN(f))
                farr[i]=0.0f;
            else farr[i]=f.floatValue();
        }
        return farr;
    }

    /**
     *
     * @param arr
     * @return
     */
    public static Float[] float2Float(float[] arr)
    {
        Float[] farr = new Float[arr.length];
        for (int i=0;i<arr.length;i++ ) {
            float f = arr[i];
            if(Float.isNaN(f))
                farr[i]=0.0f;
            else farr[i]=f;
        }
        return farr;
    }
    /**
     *
     * @return
     */
    public static ModelInfo WithDefaultParams()
    {
        ModelInfo info = new ModelInfo();
        info.setMeanVals(new Float[]{103.53f, 116.28f, 123.675f});
        info.setNormalVals(new Float[]  { 1 / 255.f, 1 / 255.f, 1 / 255.f });
        info.setTargetSize(320.f);
        info.setInputName("images");
        info.setOutputName("output");
        return info;
    }
}
