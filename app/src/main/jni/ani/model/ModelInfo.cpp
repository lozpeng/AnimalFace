//
// Created by lozpeng on 2024/1/8.
//
#include "ModelInfo.hpp"
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace ani{
    /**
     * 模型信息
     */
   class ModelInfo::Impl{
   public:
       std::string modelId;             //模型编号
       std::string modelName;           //模型名称
       std::string inputName;           //输入名称
       std::string outputName;          //输出名称
       int classes;                     //类数量
       int cpuGpu;                      //使用CPU或GPU
       int targetSize;                  //目标大小
       std::vector<float>  meanVals;   //数组，
       std::vector<float>  normals;    //数组
   };
    ModelInfo::ModelInfo()
            : impl_(std::make_unique<Impl>()) {}
    ModelInfo::~ModelInfo() = default;

    // movable
    ModelInfo::ModelInfo(ModelInfo&&) noexcept = default;
    ModelInfo& ModelInfo::operator=(ModelInfo&&) noexcept = default;

// copyable
    ModelInfo::ModelInfo(const ModelInfo& options)
            : impl_(std::make_unique<Impl>(*options.impl_)) {}

    ModelInfo ModelInfo::clone() const {
        return ModelInfo(*this);
    }

    ModelInfo& ModelInfo::withModelName(std::string modelName)
    {
        impl_->modelName = std::move(modelName);
        return *this;
    }

    const std::string& ModelInfo::modelName() const
    {
        return impl_->modelName;

    }

    ModelInfo& ModelInfo::withModelId(std::string modelId)
    {
        impl_->modelId = std::move(modelId);
        return *this;
    }

    const std::string& ModelInfo::modelId() const
    {
        return impl_->modelId;
    }

    ModelInfo& ModelInfo::withInputName(std::string inputName)
    {
        impl_->inputName = std::move(inputName);
        return *this;
    }

    const std::string& ModelInfo::inputName()const
    {
        return impl_->inputName;
    }

    ModelInfo& ModelInfo::withOutputName(std::string outputName)
    {
        impl_->outputName = std::move(outputName);
        return *this;
    }
    const std::string& ModelInfo::outputName()const
    {
        return impl_->outputName;
    }

    ModelInfo& ModelInfo::withCpuGPU(int gpu)
    {
        impl_->cpuGpu = gpu;
        return *this;
    }
    const int& ModelInfo::gpu() const
    {
        return impl_->cpuGpu;
    }

    ModelInfo& ModelInfo::withTargetSize(int targetSize)
    {
        impl_->targetSize = targetSize;
        return *this;
    }
    const int& ModelInfo::targetSize() const
    {
        return impl_->targetSize;
    }

    ModelInfo& ModelInfo::withMeanVals(std::vector<float> meanVals)
    {
        impl_->meanVals = std::move(meanVals);
        return *this;
    }
    const std::vector<float> ModelInfo::meanVals()const
    {
        return impl_->meanVals;
    }

    ModelInfo& ModelInfo::withNormals(std::vector<float> normals)
    {
        impl_->normals = std::move(normals);
        return *this;
    }
    const std::vector<float> ModelInfo::normals()const
    {
        return impl_->normals;
    }

    ModelInfo& ModelInfo::withClasses(int classes)
    {
        impl_->classes = classes;
        return *this;
    }
    const int& ModelInfo::classes() const
    {
        return impl_->classes;
    }

    ModelInfo ModelInfo::DefaultModelInfo()
    {
        return YoloV8sModelInfo();
    }

    ModelInfo ModelInfo::YoloV8sModelInfo(){

        ModelInfo modelInfo = ModelInfo()
                .withModelId("001")
                .withModelName("Yolov8s")
                .withClasses(60)
                .withCpuGPU(0)
                .withTargetSize(648);
        return modelInfo;
    }
}