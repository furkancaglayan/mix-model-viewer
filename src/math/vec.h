#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using vec1 = glm::vec1;
using vec2 = glm::vec2;
using vec3 = glm::vec3;
using vec4 = glm::vec4;

static vec3 normalize (const vec3& v)
{
    return glm::normalize (v);
}

static vec3 cross (const vec3& v1, const vec3& v2)
{
    return glm::cross (v1, v2);
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