#pragma once
#include "vec.h"

using mat2 = glm::mat2;
using mat3 = glm::mat3;
using mat4 = glm::mat4;

static mat4 perspective (float fov, float aspect, float near_cam, float far_cam)
{
    return glm::perspective (glm::radians (fov), aspect, near_cam, far_cam);
}

static mat4 ortho (float left, float right, float bottom, float top)
{
    return glm::ortho (left, right, bottom, top);
}

static mat4 lookat (const vec3& eye, const vec3& at, const vec3& up)
{
    return glm::lookAt (eye, at, up);
}


static mat4 rotate (const mat4& model, const float& degrees, const vec3& axis)
{
    return glm::rotate (model, glm::radians (degrees), axis);
}

/*using vec1 = vec<float, 1>;
using vec2 = vec<float, 2>;
typedef vec<float, 3> vec3;
using vec4 = vec<float, 4>;

using ivec1 = vec<int, 1>;
using ivec2 = vec<int, 2>;
using ivec3 = vec<int, 3>;
using ivec4 = vec<int, 4>;

namespace mix
{
    namespace math
    {
        template <class T, int N> struct vec
        {
            public:

            vec (glm::vec<N, T, glm::defaultp> v) : _value{ v }
            {
            }

            vec (T&&... args) : _value{ std::forward (args...) }
            {
                constexpr std::size_t n = sizeof...(T);
                static_assert (n == N);
            }

            T at (int t) const
            {
                return this[t];
            }

            T& operator[] (int i)
            {
                return _value[i];
            }


            template <class U>
            vec<T, N>& vec<N, T, glm::defaultp>::operator*= (U scalar)
            {
                for (size_t i = 0; i < N; i++)
                {
                    this->_value[i] *= static_cast<T> (scalar);
                }
                return *this;
            }

            private:

            glm::vec<N, T, glm::defaultp> _value;
        };
    } // namespace math
} // namespace mix
*/