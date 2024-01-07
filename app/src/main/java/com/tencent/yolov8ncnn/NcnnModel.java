package com.tencent.yolov8ncnn;

/**
 * 模型基本信息
 */
public class NcnnModel {
    /**
     * 模型编号，唯一编号，可以根据该编号查询一些名称基本信息
     */
    public String ModelId;
    /**
     * 模型名称
     */
    public String ModelName;
    /**
     * 输入层名称
     */
    public String InputName;

    /**
     * 输出层名称
     */
    public String OutputName;
    /**
     * 使用GPU或者CPU ，0表示CPU,1表示GPU
     */
    public int  GPUCPU;
    /**
     * 目标大小
     */
    public  int TargetSize;
    /**
     * 均值
     */
    public float[] MeanVals;
    /**
     *
     */
    public float[] Normals;
}
