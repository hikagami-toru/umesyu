#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cmath>

template<typename T, size_t N>
struct vector {
    using value_type = T;
    using reference = T&;
    using const_reference = T const&;
    using iterator = T*;
    using const_iterator = T const*;
    using difference_type = std::ptrdiff_t;
    using size_type = size_t;
    static constexpr size_t size = N;

    value_type const& operator[](int i) const {
        return elems[i];
    }
    value_type& operator[](int i) {
        return elems[i];
    }

    vector& operator+=(vector const& rhs) {
        for (size_t i = 0; i < size; ++i)
            elems[i] += rhs[i];
        return *this;
    }
    vector& operator-=(vector const& rhs) {
        for (size_t i = 0; i < size; ++i)
            elems[i] -= rhs[i];
        return *this;
    }
    vector& operator*=(value_type const& rhs) {
        for (auto& e : elems)
            e *= rhs;
        return *this;
    }
    vector& operator/=(value_type const& rhs) {
        for (auto& e : elems)
            e /= rhs;
        return *this;
    }

    value_type length2() const {
        value_type result{};
        for (auto const& e : elems)
            result += e*e;
        return result;
    }
    value_type length() const {
        return std::sqrt(length2());
    }

    vector& normalize() {
        value_type len = length();
        for (auto& e : elems)
            e /= len;
        return *this;
    }

    vector normal() const {
        auto result = *this;
        result.normalize();
        return result;
    }

    value_type const* data() const {
        return &elems[0];
    }

    static value_type dot(vector const& lhs, vector const& rhs) {
        value_type result{};
        for (size_t i = 0; i < size; ++i)
            result += lhs[i] * rhs[i];
        return result;
    }

    value_type elems[size];
};

template<typename T, size_t N>
static inline vector<T, N> operator+(vector<T, N> const& lhs, vector<T, N> const& rhs) {
    auto result = lhs;
    result += rhs;
    return result;
}

template<typename T, size_t N>
static inline vector<T, N> operator-(vector<T, N> const& lhs, vector<T, N> const& rhs) {
    auto result = lhs;
    result -= rhs;
    return result;
}

template<typename T, size_t N>
static inline vector<T, N> operator*(vector<T, N> const& lhs, T const& rhs) {
    auto result = lhs;
    result *= rhs;
    return result;
}

template<typename T, size_t N>
static inline vector<T, N> operator*(T const& lhs, vector<T, N> const& rhs) {
    return rhs * lhs;
}

template<typename T, size_t N>
static inline vector<T, N> operator/(vector<T, N> const& lhs, T const& rhs) {
    auto result = lhs;
    result /= rhs;
    return result;
}

using vector3d = vector<double, 3>;


static inline vector3d cross(vector3d const& lhs, vector3d const& rhs) {
    return vector3d{{
        lhs[1]*rhs[2] - lhs[2]*rhs[1],
        lhs[2]*rhs[0] - lhs[0]*rhs[2],
        lhs[0]*rhs[1] - lhs[1]*rhs[0]
    }};
}

#endif // VECTOR_HPP
