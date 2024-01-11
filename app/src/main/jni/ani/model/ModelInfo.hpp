#pragma once
//
// Created by lozpeng on 2024/1/8.
//
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace ani{
    /**
     *
     */
    class ModelInfo final{
        public:
            explicit ModelInfo();
            ~ModelInfo();
            // movable
            ModelInfo(ModelInfo&& options) noexcept;
            ModelInfo& operator=(ModelInfo&& options) noexcept;

            // copyable
            ModelInfo(const ModelInfo&);

            ModelInfo clone() const;

            ModelInfo& withClasses(int classes);
            const int& classes() const;

            ModelInfo& withModelName(std::string modelName);

            const std::string& modelName() const;

            ModelInfo& withModelId(std::string modelId);

            const std::string& modelId() const;

            ModelInfo& withInputName(std::string inputName);
            const std::string& inputName()const;

            ModelInfo& withOutputName(std::string outputName);
            const std::string& outputName()const;

            ModelInfo& withCpuGPU(int gpu);
            const int& gpu() const;

            ModelInfo& withTargetSize(int targetSize);
            const int& targetSize() const;

            ModelInfo& withMeanVals(std::vector<float> meanVals);
            const std::vector<float> meanVals()const;

            ModelInfo& withNormals(std::vector<float> normals);
            const std::vector<float> normals()const;

            /**
             * 默认的模型信息
             * @return
             */
            static ModelInfo DefaultModelInfo();

            static ModelInfo YoloV8sModelInfo();
        private:
            class Impl;
            std::unique_ptr<Impl> impl_;
        };
}