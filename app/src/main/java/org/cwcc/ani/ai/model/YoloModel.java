package org.cwcc.ani.ai.model;

import androidx.annotation.Keep;

/**
 * 模型调用
 */
public class YoloModel {


    @Keep
    public native ModelResult[] nativeDectect();


}
