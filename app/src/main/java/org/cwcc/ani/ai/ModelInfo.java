package org.cwcc.ani.ai;

/**
 * 模型基本信息
 */
public class ModelInfo {
    /**
     * 模型编号，唯一编号，可以根据该编号查询一些名称基本信息
     */
    private String ModelId;
    /**
     * 模型名称
     */
    private String ModelName;
    /**
     * 输入层名称
     */
    private String InputName;

    /**
     * 输出层名称
     */
    private String OutputName;
    /**
     * 使用GPU或者CPU ，0表示CPU,1表示GPU
     */
    private int  GPUCPU;
    /**
     * 目标大小
     */
    private  int TargetSize;
    /**
     * 均值
     */
    private float[] MeanVals;
    /**
     *
     */
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
}
