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
    private static final String TAG = "AniAI-ModelInfo";
    @Keep
    private long nativePtr;
    protected boolean detached;

    protected ModelInfo(long nativePtr)
    {
        this.nativePtr = nativePtr;
    }
    public ModelInfo() {
    }
    public long getNativePtr() {
        return nativePtr;
    }

    @Keep
    private native void nativeDestroy();

    @Keep
    private native void nativeInitialize(ModelInfo nativeInfo);

    @Keep
    public native void setModelId(@NonNull String modelId);

    @Keep
    public native void setModelName(@NonNull String modelName);

    @Keep
    public native void setInputName(@NonNull String inputName);

    @Keep
    public native void setOutputName(@NonNull String outputName);

    @Keep
    public native void setGPUCUP(@NonNull Boolean gpucup);

    @Keep
    public native void setTargetSize(@NonNull Integer targetSize);

    @Keep
    public native void setClasses(@NonNull Integer classes);
    @Keep
    public native void setMeanVals(@NonNull Float[] meanVals);

    @Keep
    public native void setNormalVals(@NonNull Float[] normalVals);

    @NonNull
    @Keep
    public native String getModelId();

    @NonNull
    @Keep
    public native String getModelName();

    @NonNull
    @Keep
    public native String getInputName();

    @NonNull
    @Keep
    public native String getOutputName();

    @NonNull
    @Keep
    public native Boolean getGPUCUP();

    @NonNull
    @Keep
    public native Integer getTargetSize();

    @NonNull
    @Keep
    public native Integer getClasses();
    @NonNull
    @Keep
    public native Float[] getMeanVals();

    @NonNull
    @Keep
    public native Float[] getNormalVals();

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
        info.setTargetSize(320);
        info.setInputName("images");
        info.setOutputName("output");
        return info;
    }
}
