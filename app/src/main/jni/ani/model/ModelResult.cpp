//
// Created by lozpeng on 2024/1/12.
//

#include "ModelResult.hpp"
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace ani {
    class ModelResult::Impl{
    public:
        float x;  //监测的结果起始位置
        float y; //监测的结果起始位置
        float w; //目标物在图像的宽度
        float h; //目标物在图像的高度
        bool isLabel;// 标识是否为标识
        float prob;     //目标识别结果置信度
        std::string label; //目标物注释
    };
    ModelResult::ModelResult()
            : impl_(std::make_unique<ModelResult::Impl>()) {}

     ModelResult::~ModelResult()=default;
    // movable
    ModelResult::ModelResult(ModelResult&& options) noexcept= default;
    ModelResult& ModelResult:: operator=(ModelResult&& options) noexcept= default;

    // copyable
    ModelResult::ModelResult(const ModelResult& options): impl_(std::make_unique<Impl>(*options.impl_)) {}

    ModelResult  ModelResult::clone() const {
        return ModelResult(*this);
    }

    ModelResult&  ModelResult::withX(float x)
    {
        impl_->x = x;
        return *this;
    }
    const float&  ModelResult::x()const
    {
        return impl_->x;
    }

    ModelResult&  ModelResult::withY(float y)
    {
        impl_->y = y;
        return *this;

    }
    const float&  ModelResult::y()const
    {
        return impl_->y;
    }


    ModelResult&  ModelResult::withW(float w)
    {
        impl_->w = w;
        return *this;
    }
    const float&  ModelResult::w()const
    {
        return impl_->w;
    }


    ModelResult&  ModelResult::withH(float h)
    {
        impl_->h = h;
        return *this;
    }
    const float&  ModelResult::h()const
    {
        return impl_->h;
    }

    ModelResult&  ModelResult::withLabel(std::string label )
    {
        impl_->label = std::move(label);
        return *this;
    }
    const std::string&  ModelResult::label()const
    {
        return impl_->label;
    }

    ModelResult&  ModelResult::withIsLabel(bool isLabel) {
        impl_->isLabel = isLabel;
        return *this;
    }
    const bool&  ModelResult::isLabel()const {
        return impl_->isLabel;

    }

    ModelResult&  ModelResult::withProb(float prob) {
        impl_->prob = prob;
        return *this;
    }
    const float& ModelResult::prob()const
    {
        return impl_->prob;
    }
} // ani