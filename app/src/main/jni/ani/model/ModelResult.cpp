//
// Created by lozpeng on 2024/1/21.
//

#include "ModelResult.hpp"

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
    ModelResult::ModelResult() :impl_(std::make_unique<ModelResult::Impl>())
    {}

    ModelResult::~ModelResult()= default;

    ModelResult::ModelResult(ModelResult&& options)  noexcept = default;

    ModelResult& ModelResult::operator=(ModelResult&&) noexcept = default;

    // copyable
    ModelResult::ModelResult(const ModelResult& options)
            : impl_(std::make_unique<Impl>(*options.impl_)) {}

    ModelResult ModelResult::clone() const {
        return ModelResult(*this);
    }


    ModelResult& ModelResult::withX(float x) {
        impl_->x = x;
        return *this;
    }
    ModelResult& ModelResult::withY(float y){
        impl_->y = y;
        return *this;
    }
    ModelResult& ModelResult::withW(float w){
        impl_->w = w;
        return *this;
    }
    ModelResult& ModelResult::withH(float h){
        impl_->h = h;
        return *this;
    }
    ModelResult& ModelResult::withLabel(std::string label ){
        impl_->label = std::move(label);
        return *this;
    }
    ModelResult& ModelResult::ModelResult::withIsLabel(bool isLabel){
        impl_->isLabel = isLabel;
        return *this;
    }
    ModelResult& ModelResult::withProb(float prob){
        impl_->prob = prob;
        return *this;
    }
    const float ModelResult::ModelResult::x() const{
        return impl_->x;
    }
    const float ModelResult::y() const{
        return impl_->y;
    }
    const float ModelResult::w() const{
        return impl_->w;
    }
    const float ModelResult::h() const{
        return impl_->h;
    }
    const float ModelResult::prob() const{
        return impl_->prob;
    }
    const std::string& ModelResult::label() const{
        return impl_->label;
    }
    const bool ModelResult::isLabel() const{
        return impl_->isLabel;
    }
} // ani