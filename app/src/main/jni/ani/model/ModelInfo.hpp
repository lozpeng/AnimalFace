//
// Created by lozpeng on 2024/1/28.
//
#pragma once

#include <memory>

namespace ani{
        /**
         * 模型信息用于C++内部进行模型信息管理
         */
        class ModelInfo final {
            private:
                class Impl;
                std::unique_ptr<Impl> impl_;
        public:
            ModelInfo();
            ~ModelInfo();

            ModelInfo(ModelInfo&&) ;
            ModelInfo(const ModelInfo& other);
            ModelInfo& operator=(const ModelInfo& other);
            ModelInfo& operator=(ModelInfo&& options);
            ModelInfo clone() const;

            ModelInfo& withModelId(std::string modelId);
            ModelInfo& withModelName(std::string modelName);
            ModelInfo& withInputName(std::string inputName);
            ModelInfo& withOutpuName(std::string outputName);
            ModelInfo& withClasses(int classes);
            ModelInfo& withCPUGPU(int cpuGPu);
            ModelInfo& withTargetSize(int targetSize);
            ModelInfo& withMeanVals(std::vector<float> meanVals);
            ModelInfo& withNormals(std::vector<float> normals);


            const std::string& getModelId() const;
            const std::string& getModelName() const;
            const std::string& getInputName() const;
            const std::string& getOutpuName() const;
            const int getClasses() const;
            const int getCpuGPU() const;
            const int getTargetSize() const;
            const std::vector<float>& getMeanVals() const;
            const size_t getMeanValsA(float arr[] ,size_t s) const;
            const std::vector<float>& getNormals() const;
            const size_t getNormalsA(float arr[],size_t s)const;
        };
}

