//
// Created by lozpeng on 2024/1/28.
//

#include "ModelInfo.hpp"
#include <string>
#include <vector>

namespace ani{
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
    ModelInfo::ModelInfo():
        impl_(std::make_unique<ModelInfo::Impl>()){}

    ModelInfo::~ModelInfo()=default;
    ModelInfo::ModelInfo(ModelInfo&&) noexcept = default;
    ModelInfo::ModelInfo(const ModelInfo& other)
            : impl_(std::make_unique<Impl>(*other.impl_)) {}
    ModelInfo& ModelInfo::operator=(const ModelInfo& other) {
        impl_ = std::make_unique<Impl>(*other.impl_);
        return *this;
    }
    ModelInfo& ModelInfo::operator=(ModelInfo&& options) {
        swap(impl_, options.impl_);
        return *this;
    }

    ModelInfo ModelInfo::clone() const {
        return ModelInfo(*this);
    }


    ModelInfo& ModelInfo::withModelId(std::string modelId){
        impl_->modelId = std::move(modelId);
        return *this;
    }
    ModelInfo& ModelInfo::withModelName(std::string modelName){
        impl_->modelName = std::move(modelName);
        return *this;
    }
    ModelInfo& ModelInfo::withInputName(std::string inputName){
        impl_->inputName = std::move(inputName);
        return *this;
    }
    ModelInfo& ModelInfo::withOutpuName(std::string outputName){
        impl_->outputName = std::move(outputName);
        return *this;
    }
    ModelInfo& ModelInfo::withClasses(int classes){
        impl_->classes = classes;
        return *this;
    }
    ModelInfo& ModelInfo::withCPUGPU(int cpuGPu){
        impl_->cpuGpu = cpuGPu;
        return *this;
    }
    ModelInfo& ModelInfo::withTargetSize(int targetSize){
        impl_->targetSize = targetSize;
        return *this;
    }
    ModelInfo& ModelInfo::withMeanVals(std::vector<float> meanVals){
        size_t  s = meanVals.size();
        if(s>=1)
        {
            impl_->meanVals.reserve(s);
            for(int i=0;i<s;i++)
                impl_->meanVals.push_back(meanVals[i]);
        }
        return *this;
    }
    ModelInfo& ModelInfo::withNormals(std::vector<float> normals){
        size_t  s = normals.size();
        if(s>=1)
        {
            impl_->normals.reserve(s);
            for(int i=0;i<s;i++)
                impl_->normals.push_back(normals[i]);
        }
        return *this;
    }

    const std::string& ModelInfo::getModelId() const{
        return (impl_->modelId);
    }
    const std::string& ModelInfo::getModelName() const{
        return (impl_->modelName);
    }
    const std::string& ModelInfo::getInputName() const{
        return (impl_->modelName);
    }
    const std::string& ModelInfo::getOutpuName() const{
        return impl_->outputName;
    }
    const int ModelInfo::getClasses() const{
        return impl_->classes;
    }
    const int ModelInfo::getCpuGPU() const{
        return impl_->cpuGpu;
    }
    const int ModelInfo::getTargetSize() const{
        return impl_->targetSize;
    }
    const std::vector<float>& ModelInfo::getMeanVals() const{
        return impl_->meanVals;
    }
    const size_t  ModelInfo::getMeanValsA(float arr[],size_t s) const
    {
        if(impl_->meanVals.size()<=0)return 0;
        //使用sdt::copy进行vector和array的转换
        //std::vector<float> mns= impl_->meanVals;
        //float aa[mns.size()];
        //std::copy(mns.begin(), mns.end(), aa);
        size_t ss=0;
        for(int i=0;i<impl_->meanVals.size();i++)
        {
            if(i<s)
            {
                arr[i]=impl_->meanVals[i];
                ss++;
            }
        }
        return ss;
    }
    const std::vector<float>& ModelInfo::getNormals() const{
        return impl_->normals;
    }
    const size_t ModelInfo::getNormalsA(float arr[],size_t s)const
    {
        if(impl_->normals.size()<=0)return 0;
        size_t ss=0;
        for(int i=0;i<impl_->normals.size();i++)
        {
            if(i<s)
            {
                arr[i]=impl_->normals[i];
                ss++;
            }
        }
        return ss;
    }
}//namespace ani