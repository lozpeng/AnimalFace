package org.cwcc.ani.ai.model;

/**
 * 模型运行后结果，模型返回后应该是一个列表
 */
public class ModelResult {
    private float x;  //监测的结果起始位置
    private float y; //监测的结果起始位置
    private float w; //目标物在图像的宽度
    private float h; //目标物在图像的高度
    private String label; //目标物注释
    private boolean isLabel;// 标识是否为标识
    private float prob;     //目标识别结果置信度
    private long peer;

    public ModelResult(){initialize();}
    protected native void initialize();
    protected native void finalize() throws Throwable;
    /**
     *
     * @param x
     * @param y
     * @param w
     * @param h
     * @param label
     * @param isLabel
     * @param prb
     */
    public ModelResult(float x,float y,float w,float h,String label,boolean isLabel,float prb)
    {
        this.setX(x);
        this.setY(y);
        this.setH(h);
        this.setW(w);
        this.setLabel(label);
        this.setIsLabel(isLabel);
        this.setProb(prb);
        initialize();
    }

    public float getX() {
        return x;
    }

    public void setX(float x) {
        this.x = x;
    }

    public float getY() {
        return y;
    }

    public void setY(float y) {
        this.y = y;
    }

    public float getW() {
        return w;
    }

    public void setW(float w) {
        this.w = w;
    }

    public float getH() {
        return h;
    }

    public void setH(float h) {
        this.h = h;
    }

    public String getLabel() {
        return label;
    }

    public void setLabel(String label) {
        this.label = label;
    }

    public boolean isLabel() {
        return isLabel;
    }

    public void setIsLabel(boolean label) {
        isLabel = label;
    }

    public float getProb() {
        return prob;
    }

    public void setProb(float prob) {
        this.prob = prob;
    }
}
