# ncnn-android-yolov8

The yolov8 object detection

This is a sample ncnn android project, it depends on ncnn library and opencv

https://github.com/Tencent/ncnn

https://github.com/nihui/opencv-mobile

https://blog.halashuo.cn/index.php/archives/118/

## how to build and run
### step1
https://github.com/Tencent/ncnn/releases
https://github.com/Tencent/ncnn/releases/latest/download/ncnn-20231027-android-vulkan.zip
* Download ncnn-YYYYMMDD-android-vulkan.zip or build ncnn for android yourself
* Extract ncnn-YYYYMMDD-android-vulkan.zip into **app/src/main/jni** and change the **ncnn_DIR** path to yours in **app/src/main/jni/CMakeLists.txt**

### step2
https://github.com/nihui/opencv-mobile
建议下载opencv android sdk 版本4.8.1 
https://github.com/opencv/opencv/releases

* Download opencv-mobile-XYZ-android.zip
* Extract opencv-mobile-XYZ-android.zip into **app/src/main/jni** and change the **OpenCV_DIR** path to yours in **app/src/main/jni/CMakeLists.txt**

### step3
* Open this project with Android Studio, build it and enjoy!

https://convertmodel.com/

YOLOV8训练的模型 转为ncnn 在Android中使用 需要一下两步，然后导出模型
1.修改Python39\Lib\site-packages\ultralytics\nn\modules\head.py
class Detect(nn.Module):
...
def forward(self, x):
    """Concatenates and returns predicted bounding boxes and class probabilities."""
    shape = x[0].shape  # BCHW
    for i in range(self.nl):
    x[i] = torch.cat((self.cv2[i](x[i]), self.cv3[i](x[i])), 1)
    if self.training:
    return x
    elif self.dynamic or self.shape != shape:
    self.anchors, self.strides = (x.transpose(0, 1) for x in make_anchors(x, self.stride, 0.5))
    self.shape = shape
    pred = torch.cat([xi.view(shape[0], self.no, -1) for xi in x], 2).permute(0, 2, 1)
    return pred

2.修改Python39\Lib\site-packages\ultralytics\nn\modules\block.py
class C2f(nn.Module):
...
def forward(self, x):
    """Forward pass through C2f layer."""
    x=self.cv1(x)
    x=[x,x[:,self.c:,...]]
    x.extend(m(x[-1]) for m in self.m)
    x.pop(1)
    return self.cv2(torch.cat(x,1))
    #y = list(self.cv1(x).chunk(2, 1))
    #y.extend(m(y[-1]) for m in self.m)
    #return self.cv2(torch.cat(y, 1))
3. 导出模型
   bird_model = YOLO(r'birds_200.pt')
   success = bird_model.export(format="onnx", simplify=True, opset=12)
4. 转换模型类型
   https://convertmodel.com/

## some notes
* Android ndk camera is used for best efficiency
* Crash may happen on very old devices for lacking HAL3 camera interface
* All models are manually modified to accept dynamic input shape
* Most small models run slower on GPU than on CPU, this is common
* FPS may be lower in dark environment because of longer camera exposure time

## screenshot
![](screenshot.png)

## Reference：  
https://github.com/nihui/ncnn-android-nanodet  
https://github.com/Tencent/ncnn  
https://github.com/ultralytics/assets/releases/tag/v0.0.0
