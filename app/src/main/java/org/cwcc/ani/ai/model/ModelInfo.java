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
    public ModelInfo(){}
    /**
     * 构造函数
     * @param mId
     * @param mName
     * @param inName
     * @param outName
     * @param cls
     * @param cpu
     * @param tSize
     * @param means
     * @param norms
     */
    public ModelInfo(
            String mId,
            String mName,
            String inName,
            String outName,
            Integer cls,
            Integer cpu,
            Integer tSize,
            Float[] means,
            Float[] norms
    ){
        this.setModelId(mId);
        this.setModelName(mName);
        this.setInputName(inName);
        this.setOutputName(outName);
        this.setClasses(cls);
        this.setCpuGpu(cpu);
        this.setTargetSize(tSize);
        this.setMeanVals(means);
        this.setNormals(norms);
    }

    @Keep
    private String modelId;
    @Keep
    private String modelName;
    @Keep
    private String inputName;
    @Keep
    private String outputName;
    @Keep
    private Integer classes;                     //类数量
    @Keep
    private Integer cpuGpu;                      //使用CPU或GPU
    @Keep
    private Integer targetSize;                  //目标大小
    @Keep
    private Float[]  meanVals;   //数组，
    @Keep
    private Float[]  normals;    //数组

    public String getModelId() {
        return modelId;
    }

    public void setModelId(String modelId) {
        this.modelId = modelId;
    }

    public String getModelName() {
        return modelName;
    }

    public void setModelName(String modelName) {
        this.modelName = modelName;
    }

    public String getInputName() {
        return inputName;
    }

    public void setInputName(String inputName) {
        this.inputName = inputName;
    }

    public String getOutputName() {
        return outputName;
    }

    public void setOutputName(String outputName) {
        this.outputName = outputName;
    }

    public Integer getClasses() {
        return classes;
    }

    public void setClasses(Integer classes) {
        this.classes = classes;
    }

    public Integer getCpuGpu() {
        return cpuGpu;
    }

    public void setCpuGpu(Integer cpuGpu) {
        this.cpuGpu = cpuGpu;
    }

    public Integer getTargetSize() {
        return targetSize;
    }

    public void setTargetSize(Integer targetSize) {
        this.targetSize = targetSize;
    }

    public Float[] getMeanVals() {
        return meanVals;
    }

    public void setMeanVals(Float[] meanVals) {
        this.meanVals = meanVals;
    }

    public Float[] getNormals() {
        return normals;
    }

    public void setNormals(Float[] normals) {
        this.normals = normals;
    }

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
        info.setNormals(new Float[]  { 1 / 255.f, 1 / 255.f, 1 / 255.f });
        info.setTargetSize(320);
        info.setInputName("images");
        info.setOutputName("output");
        return info;
    }
}
