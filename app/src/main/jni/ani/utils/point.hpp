//
// Created by lozpeng on 2024/1/12.
//

#ifndef ANIMALFACE_POINT_HPP
#define ANIMALFACE_POINT_HPP
namespace ani{
    template <typename T>
    struct point
    {
        using coordinate_type = T;

        constexpr point()
                : x(), y()
        {
        }
        constexpr point(T x_, T y_)
                : x(x_), y(y_)
        {
        }

        T x;
        T y;
    };
    template <class T>
    using Point = ani::point<T>;
}//namespace ani
#endif //ANIMALFACE_POINT_HPP
