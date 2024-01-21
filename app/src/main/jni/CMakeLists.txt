project(ani)

cmake_minimum_required(VERSION 3.10)
set(OpenCV_DIR ${CMAKE_SOURCE_DIR}/opencv-4.8.1-android-sdk/sdk/native/jni)
set(JNI_DIR ${CMAKE_SOURCE_DIR}/jni.hpp/include)
set(ncnn_DIR ${CMAKE_SOURCE_DIR}/ncnn-20231027-android-vulkan/${ANDROID_ABI}/lib/cmake/ncnn)
set(ANI_DIR ${CMAKE_SOURCE_DIR}/ani)

find_package(OpenCV REQUIRED core imgproc)
find_package(OpenCV REQUIRED core imgproc calib3d)
find_package(ncnn REQUIRED)

include_directories(${ANI_DIR}
                    ${JNI_DIR}
                    ${ANI_DIR}/utils
                    )
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/utils)

add_library(ani SHARED
        ${ANI_DIR}/yolov8ncnn.cpp
        ${ANI_DIR}/yolo.cpp
        ${ANI_DIR}/ndkcamera.cpp
        ${ANI_DIR}/jni_native.hpp
        ${ANI_DIR}/jni_native.cpp
        ${ANI_DIR}/java_types.hpp
        ${ANI_DIR}/java_types.cpp
        ${ANI_DIR}/ani_jni.hpp
        ${ANI_DIR}/ani_jni.cpp
        ${ANI_DIR}/utils/utils.cpp
        ${ANI_DIR}/utils/utils.hpp
        ${ANI_DIR}/utils/noncopyable.hpp
        ${ANI_DIR}/YoloModel.hpp
        ${ANI_DIR}/YoloModel.cpp
        ${ANI_DIR}/utils/size.hpp
        ${ANI_DIR}/model/image.hpp
        ${ANI_DIR}/model/ModelResult.cpp
        ${ANI_DIR}/model/ModelResult.hpp
        #--android
        ${ANI_DIR}/model/android/AniModelResult.cpp
        ${ANI_DIR}/model/android/AniModelResult.hpp
        ${ANI_DIR}/model/android/ModelInfo.cpp
        ${ANI_DIR}/model/android/ModelInfo.hpp
        ${ANI_DIR}/model/android/ModelResult.cpp
        ${ANI_DIR}/model/android/ModelResult.hpp
        ${ANI_DIR}/model/android/attach_env.cpp
        ${ANI_DIR}/model/android/attach_env.cpp
        ${ANI_DIR}/model/android/Bitmap.cpp
        ${ANI_DIR}/model/android/Bitmap.hpp
        ${ANI_DIR}/model/android/conversion/collection.hpp
        ${ANI_DIR}/model/android/conversion/collection.cpp
        ${ANI_DIR}/model/android/conversion/conversion.hpp
        ${ANI_DIR}/model/android/conversion/conversion.cpp
        )

target_link_libraries(ani ncnn ${OpenCV_LIBS} camera2ndk mediandk)
