package org.cwcc.ani.ai.model;

import android.os.Parcel;
import android.os.Parcelable;

import androidx.annotation.Keep;
import androidx.annotation.NonNull;

/**
 * 模型基本信息
 */
public class ModelInfo implements Parcelable {
    /**
     *
     * @param modelId
     * @param modelName
     * @param inputName
     * @param outpuName
     * @param cpuGpu
     * @param targetSize
     * @param classes
     * @param meanVals
     * @param normals
     */
    @Keep
    public ModelInfo(
            String modelId,
            String modelName,
            String inputName,
            String outpuName,
            int cpuGpu,
            int targetSize,
            int classes,
            float[] meanVals,
            float[] normals
    )
    {
        this.ModelId=modelId;
        this.ModelName=modelName;
        this.InputName = inputName;
        this.OutputName = outpuName;
        this.GPUCPU = cpuGpu;
        this.TargetSize = targetSize;
        this.MeanVals = meanVals;
        this.Normals = normals;
        this.Classes = classes;
    }

    /**
     * 无参数构造函数
     */
    public ModelInfo(){}

    protected ModelInfo(Parcel in) {
        ModelId = in.readString();
        ModelName = in.readString();
        InputName = in.readString();
        OutputName = in.readString();
        GPUCPU = in.readInt();
        TargetSize = in.readInt();
        Classes = in.readInt();
        MeanVals = in.createFloatArray();
        Normals = in.createFloatArray();
    }

    public static final Creator<ModelInfo> CREATOR = new Creator<ModelInfo>() {
        @Override
        public ModelInfo createFromParcel(Parcel in) {
            return new ModelInfo(in);
        }

        @Override
        public ModelInfo[] newArray(int size) {
            return new ModelInfo[size];
        }
    };

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(@NonNull Parcel dest, int flags) {
        dest.writeString(ModelId);
        dest.writeString(ModelName);
        dest.writeString(InputName);
        dest.writeString(OutputName);
        dest.writeInt(GPUCPU);
        dest.writeInt(TargetSize);
        dest.writeInt(Classes);
        dest.writeFloatArray(MeanVals);
        dest.writeFloatArray(Normals);
    }
    /**
     * 模型编号，唯一编号，可以根据该编号查询一些名称基本信息
     */
    @Keep
    private String ModelId;
    /**
     * 模型名称
     */
    @Keep
    private String ModelName;
    /**
     * 输入层名称
     */
    @Keep
    private String InputName;

    /**
     * 输出层名称
     */
    @Keep
    private String OutputName;
    /**
     * 使用GPU或者CPU ，0表示CPU,1表示GPU
     */
    @Keep
    private int  GPUCPU;
    /**
     * 目标大小
     */
    @Keep
    private  int TargetSize;
    /**
     * 类数目
     */
    @Keep
    private int Classes;
    /**
     * 均值
     */
    @Keep
    private float[] MeanVals;
    /**
     *
     */
    @Keep
    private float[] Normals;

    public String getModelId() {
        return ModelId;
    }

    public void setModelId(String modelId) {
        ModelId = modelId;
    }

    public String getModelName() {
        return ModelName;
    }

    public void setModelName(String modelName) {
        ModelName = modelName;
    }

    public String getInputName() {
        return InputName;
    }

    public void setInputName(String inputName) {
        InputName = inputName;
    }

    public String getOutputName() {
        return OutputName;
    }

    public void setOutputName(String outputName) {
        OutputName = outputName;
    }

    public int getGPUCPU() {
        return GPUCPU;
    }

    public void setGPUCPU(int GPUCPU) {
        this.GPUCPU = GPUCPU;
    }

    public int getTargetSize() {
        return TargetSize;
    }

    public void setTargetSize(int targetSize) {
        TargetSize = targetSize;
    }

    public float[] getMeanVals() {
        return MeanVals;
    }

    public void setMeanVals(float[] meanVals) {
        MeanVals = meanVals;
    }

    public float[] getNormals() {
        return Normals;
    }

    public void setNormals(float[] normals) {
        Normals = normals;
    }

    public int getClasses() {
        return Classes;
    }

    public void setClasses(int classes) {
        Classes = classes;
    }

    /**
     * 一个C++函数，用来与java端交互的
     * @return
     */
    public static  native ModelInfo defaultModelInfo();

    /**
     *
     * @return
     */
    public static ModelInfo WithDefaultParams()
    {
        ModelInfo info = new ModelInfo(  );
        info.Normals = new float[]  { 1 / 255.f, 1 / 255.f, 1 / 255.f };
        info.MeanVals = new float[]{103.53f, 116.28f, 123.675f};
        info.TargetSize = 320;
        info.InputName = "images";
        info.OutputName = "output";

        return info;
    }
}
