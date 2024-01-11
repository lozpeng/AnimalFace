package org.cwcc.ani.ai.model;

import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.view.Surface;

public class Yolov8Model {
    public native boolean loadModel(AssetManager mgr, int modelid, int cpugpu);

    public native boolean openCamera(int facing);
    public native boolean closeCamera();
    public native boolean setOutputWindow(Surface surface);


    public native void toValue(float[] vals);

    public native float[] getFloatValue();

    static {
        System.loadLibrary("ani");
    }
    public class Obj
    {
        public float x;
        public float y;
        public float w;
        public float h;
        public String label;
        public float prob;

    }
    public native Yolov8Model.Obj[] Detect(Bitmap bitmap);
}
