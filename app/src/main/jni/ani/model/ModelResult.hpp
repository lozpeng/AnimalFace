//
// Created by lozpeng on 2024/1/21.
//
#ifndef ANIMALFACE_MODELRESULT_HPP
#define ANIMALFACE_MODELRESULT_HPP

#include <iostream>
#include <string>

namespace ani {
    /**
     * 模型计算返回结果
     */
    class ModelResult final{
    private:
        class Impl;
        std::unique_ptr<Impl> impl_;
    public:
        explicit ModelResult();
        ~ModelResult();
        ModelResult(ModelResult&& options) noexcept;  //
        ModelResult& operator=(ModelResult&& options) noexcept; //

        // copyable
        ModelResult(const ModelResult&);

        ModelResult clone() const;

        ModelResult& withX(float x);
        ModelResult& withY(float y);
        ModelResult& withW(float w);
        ModelResult& withH(float h);
        ModelResult& withLabel(std::string label );
        ModelResult& withIsLabel(bool isLabel);
        ModelResult& withProb(float prob);
        const float x() const;
        const float y() const;
        const float w() const;
        const float h() const;
        const float prob() const;
        const std::string& label() const;
        const bool isLabel() const;
    };
} // ani
#endif //ANIMALFACE_MODELRESULT_HPP
