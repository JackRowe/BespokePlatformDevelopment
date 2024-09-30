#pragma once

#include <tuple>
#include <cmath>

template <typename T>
struct Vector2 {
    T x, y;

    // both empty, filled and partially filled constructors
    Vector2() : x(0), y(0) {}
    Vector2(T x) : x(x), y(x) {}
    Vector2(T x, T y) : x(x), y(y) {}

#pragma region mathmatic operations
    // add
    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    // add in place
    Vector2& operator+=(const Vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    // subtract
    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }

    // subtract in place
    Vector2& operator-=(const Vector2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    // multiply by scalar
    Vector2 operator*(T scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    // multiply in place by scalar
    Vector2& operator*=(T scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    // multiply by vector
    Vector2 operator*(const Vector2& vector) const {
        return Vector2(x * vector.x, y * vector.y);
    }

    // multiply in place by vector
    Vector2 operator*(const Vector2& vector) {
        x *= vector.x;
        y *= vector.y;
        return *this;
    }

    // divide by scalar
    Vector2 operator/(T scalar) const {
        return Vector2(x / scalar, y / scalar);
    }

    // divide in place by scalar
    Vector2& operator/=(T scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    // divide by vector
    Vector2 operator/(const Vector2& vector) const {
        return Vector2(x / vector.x, y / vector.y);
    }

    // divide in place by vector
    Vector2& operator/=(const Vector2& vector) {
        x /= vector.x;
        y /= vector.y;
        return *this;
    }
#pragma endregion

#pragma region boolean operations
    // equal to
    bool operator==(const Vector2& other) const {
        return x == other.x && y == other.y;
    }

    // not equal to
    bool operator!=(const Vector2& other) const {
        return x != other.x || y != other.y;
    }

    // less than
    bool operator<(const Vector2& other) const {
        return std::tie(x, y) < std::tie(other.x, other.y);
    }

    // greater than
    bool operator>(const Vector2& other) const {
        return std::tie(x, y) > std::tie(other.x, other.y);
    }

    // less than or equal to
    bool operator<=(const Vector2& other) const {
        return std::tie(x, y) <= std::tie(other.x, other.y);
    }

    // greater than or equal to
    bool operator>=(const Vector2& other) const {
        return std::tie(x, y) >= std::tie(other.x, other.y);
    }
#pragma endregion

#pragma region functions
    T length() const {
        return std::sqrt(static_cast<T>(x * x + y * y));
    }

    Vector2 normalize() const {
        T length = length();

        if (length == static_cast<T>(0)) return *this;

        return Vector2<T>(x / length, y / length);
    }

    T dot(const Vector2& other) const {
        return x * other.x + y * other.y;
    }

    T cross(const Vector2& other) const {
        return x * other.y - y * other.x;
    }
#pragma endregion
};

template <typename T>
struct Vector3 {
    T x, y, z;

    // both empty and filled constructors
    Vector3() : x(0), y(0), z(0) {}
    Vector3(T x) : x(x), y(x), z(x) {}
    Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

#pragma region mathmatic operations

    // add
    Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    // add in place
    Vector3& operator+=(const Vector3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    // subtract
    Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    // subtract in place
    Vector3& operator-=(const Vector3& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    // multiply by scalar
    Vector3 operator*(T scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    // multiply in place by scalar
    Vector3& operator*=(T scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    // multiply by vector
    Vector3 operator*(const Vector3& vector) const {
        return Vector3(x * vector.x, y * vector.y, z * vector.z);
    }

    // multiply in place by vector
    Vector3& operator*=(const Vector3& vector) {
        x *= vector.x;
        y *= vector.y;
        z *= vector.z;
        return *this;
    }

    // divide by scalar
    Vector3 operator/(T scalar) const {
        return Vector3(x / scalar, y / scalar, z / scalar);
    }

    // divide in place by scalar
    Vector3& operator/=(T scalar) {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    // divide by vector
    Vector3 operator/(const Vector3& vector) const {
        return Vector3(x / vector.x, y / vector.y, z / vector.z);
    }

    // divide in place by vector
    Vector3& operator/=(const Vector3& vector) {
        x /= vector.x;
        y /= vector.y;
        z /= vector.z;
        return *this;
    }

#pragma endregion

#pragma region boolean operations

    // equal to
    bool operator==(const Vector3& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    // not equal to
    bool operator!=(const Vector3& other) const {
        return x != other.x || y != other.y || z != other.z;
    }

    // less than
    bool operator<(const Vector3& other) const {
        return std::tie(x, y, z) < std::tie(other.x, other.y, other.z);
    }

    // greater than
    bool operator>(const Vector3& other) const {
        return std::tie(x, y, z) > std::tie(other.x, other.y, other.z);
    }

    // less than or equal to
    bool operator<=(const Vector3& other) const {
        return std::tie(x, y, z) <= std::tie(other.x, other.y, other.z);
    }

    // greater than or equal to
    bool operator>=(const Vector3& other) const {
        return std::tie(x, y, z) >= std::tie(other.x, other.y, other.z);
    }

#pragma endregion

#pragma region functions

    T length() const {
        return std::sqrt(static_cast<T>(x * x + y * y + z * z));
    }

    Vector3 normalize() const {
        T len = length();
        if (len == static_cast<T>(0)) return *this;
        return Vector3<T>(x / len, y / len, z / len);
    }

    T dot(const Vector3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3 cross(const Vector3& other) const {
        return Vector3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

#pragma endregion
};

template <typename T>
struct Vector4 {
    T x, y, z, w;

    // both empty and filled constructors
    Vector4() : x(0), y(0), z(0), w(0) {}
    Vector4(T x) : x(x), y(x), z(x), w(x) {}
    Vector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

#pragma region mathmatic operations

    // add
    Vector4 operator+(const Vector4& other) const {
        return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    // add in place
    Vector4& operator+=(const Vector4& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
    }

    // subtract
    Vector4 operator-(const Vector4& other) const {
        return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    // subtract in place
    Vector4& operator-=(const Vector4& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
        return *this;
    }

    // multiply by scalar
    Vector4 operator*(T scalar) const {
        return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
    }

    // multiply in place by scalar
    Vector4& operator*=(T scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;
        return *this;
    }

    // multiply by vector
    Vector4 operator*(const Vector4& vector) const {
        return Vector4(x * vector.x, y * vector.y, z * vector.z, w * vector.w);
    }

    // multiply in place by vector
    Vector4& operator*=(const Vector4& vector) {
        x *= vector.x;
        y *= vector.y;
        z *= vector.z;
        w *= vector.w;
        return *this;
    }

    // divide by scalar
    Vector4 operator/(T scalar) const {
        return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
    }

    // divide in place by scalar
    Vector4& operator/=(T scalar) {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        w /= scalar;
        return *this;
    }

    // divide by vector
    Vector4 operator/(const Vector4& vector) const {
        return Vector4(x / vector.x, y / vector.y, z / vector.z, w / vector.w);
    }

    // divide in place by vector
    Vector4& operator/=(const Vector4& vector) {
        x /= vector.x;
        y /= vector.y;
        z /= vector.z;
        w /= vector.w;
        return *this;
    }

#pragma endregion

#pragma region boolean operations

    // equal to
    bool operator==(const Vector4& other) const {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    // not equal to
    bool operator!=(const Vector4& other) const {
        return x != other.x || y != other.y || z != other.z || w != other.w;
    }

    // less than
    bool operator<(const Vector4& other) const {
        return std::tie(x, y, z, w) < std::tie(other.x, other.y, other.z, other.w);
    }

    // greater than
    bool operator>(const Vector4& other) const {
        return std::tie(x, y, z, w) > std::tie(other.x, other.y, other.z, other.w);
    }

    // less than or equal to
    bool operator<=(const Vector4& other) const {
        return std::tie(x, y, z, w) <= std::tie(other.x, other.y, other.z, other.w);
    }

    // greater than or equal to
    bool operator>=(const Vector4& other) const {
        return std::tie(x, y, z, w) >= std::tie(other.x, other.y, other.z, other.w);
    }

#pragma endregion

#pragma region functions

    T length() const {
        return std::sqrt(static_cast<T>(x * x + y * y + z * z + w * w));
    }

    Vector4 normalize() const {
        T len = length();
        if (len == static_cast<T>(0)) return *this;
        return Vector4<T>(x / len, y / len, z / len, w / len);
    }

    T dot(const Vector4& other) const {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    // Vector4 cross(const Vector4& other) const {
    //     return Vector4(
    //         y * other.z - z * other.y,
    //         z * other.x - x * other.z,
    //         x * other.y - y * other.x,
    //         0
    //     );
    // }

#pragma endregion
};