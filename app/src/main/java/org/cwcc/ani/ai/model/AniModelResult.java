package org.cwcc.ani.ai.model;

import android.os.Build;
import android.os.Parcel;
import android.os.Parcelable;

import androidx.annotation.Keep;
import androidx.annotation.NonNull;

/**
 * 动物信息，C++与java  链接样例，从C++端创建java对象，并是实现数据传递
 */
public class AniModelResult implements Parcelable {
    @Keep
    float x;  //监测的结果起始位置
    @Keep
    float y; //监测的结果起始位置
    @Keep
    float w; //目标物在图像的宽度
    @Keep
    float h; //目标物在图像的高度
    @Keep
    boolean isLabel;// 标识是否为标识
    @Keep
    float prob;     //目标识别结果置信度
    @Keep
    String label; //目标物注释

    AniModelResult(String label,float x,float y,float w,float h,boolean isLabeled,float prob)
    {
        this.x = x;
        this.y = y;
        this.h = h;
        this.w= w;
        this.label=label;
        this.prob = prob;
        this.isLabel =isLabeled;
    }

    protected AniModelResult(Parcel in) {
        label = in.readString();
        x = in.readFloat();
        y = in.readFloat();
        w = in.readFloat();
        h = in.readFloat();
        prob = in.readFloat();
        isLabel = in.readInt() != 0;
    }

    public static final Creator<AniModelResult> CREATOR = new Creator<AniModelResult>() {
        @Override
        public AniModelResult createFromParcel(Parcel in) {
            return new AniModelResult(in);
        }

        @Override
        public AniModelResult[] newArray(int size) {
            return new AniModelResult[size];
        }
    };

    public static native AniModelResult DefaultResult();

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

    public boolean isLabel() {
        return isLabel;
    }

    public void setLabel(boolean label) {
        isLabel = label;
    }

    public float getProb() {
        return prob;
    }

    public void setProb(float prob) {
        this.prob = prob;
    }

    public String getLabel() {
        return label;
    }

    public void setLabel(String label) {
        this.label = label;
    }

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(@NonNull Parcel dest, int flags) {
        dest.writeString(label);
        dest.writeFloat(x);
        dest.writeFloat(y);
        dest.writeFloat(w);
        dest.writeFloat(h);
        dest.writeFloat(prob);
        dest.writeInt(isLabel?1:0);
        //dest.writeBoolean(isLabel); //写入 boolean
    }
}
