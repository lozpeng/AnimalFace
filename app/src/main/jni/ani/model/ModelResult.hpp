//
// Created by lozpeng on 2024/1/12.
//

#ifndef ANIMALFACE_MODELRESULT_HPP
#define ANIMALFACE_MODELRESULT_HPP

#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace ani {
    /**
     * 模型结果
     */
    class ModelResult final{
    public:
        explicit ModelResult();
        ~ModelResult();
        // movable
        ModelResult(ModelResult&& options) noexcept;
        ModelResult& operator=(ModelResult&& options) noexcept;

        // copyable
        ModelResult(const ModelResult&);

        ModelResult clone() const;

        ModelResult& withX(float x);
        const float& x()const;

        ModelResult& withY(float y);
        const float& y()const;


        ModelResult& withW(float w);
        const float& w()const;

        ModelResult& withH(float h);
        const float& h()const;

        ModelResult& withLabel(std::string label );
        const std::string& label()const;

        ModelResult& withIsLabel(bool isLabel);
        const bool& isLabel()const;

        ModelResult& withProb(float prob);
        const float& prob()const;

    private:
        class Impl;
        std::unique_ptr<Impl> impl_;
    };
} // ani

#endif //ANIMALFACE_MODELRESULT_HPP
