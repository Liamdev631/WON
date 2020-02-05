#pragma once
#include <cmath>
#include <stdint.h>

using namespace std;

template <typename T>
struct vec2
{
	T x;
	T y;

	vec2(T x, T y)
		: x(x), y(y) { }
	vec2() : x(0), y(0) { }

	vec2<T> operator*(const T& rhs) const { return vec2<T>((T)(x * rhs), (T)(y * rhs)); }
	vec2<T> operator/(const T& rhs) const { return vec2<T>((T)(x / rhs), (T)(y / rhs)); }
	vec2<T> operator-(const vec2<T>& rhs) const { return vec2<T>((T)(x - rhs.x), (T)(y - rhs.x)); }
	vec2<T> operator+(const vec2<T>& rhs) const { return vec2<T>((T)(x + rhs.x), (T)(y + rhs.x)); }

	bool operator==(const vec2<T>& rhs) const { return x == rhs.x && y == rhs.y; };
	bool operator!=(const vec2<T>& rhs) const { return x != rhs.x || y != rhs.y; };

	float length() const
	{
		return std::sqrtf(std::powf((float)x, 2) + std::powf((float)x, 2));
	}

	void normalize()
	{
		const float length = std::sqrtf(std::powf((float)x, 2) + std::powf((float)x, 2));
		if (length == 0)
			return;
		x /= length;
		y /= length;
	}
};

typedef vec2<float> vec2f;
typedef vec2<int> vec2i;

template <typename T>
static float distance(const vec2<T>& from, const vec2<T>& to)
{
	float dx = static_cast<float>(to.x - from.x), dy = static_cast<float>(to.y - from.y);
	return std::sqrtf(dx * dx + dy * dy);
}

inline float lerp(const float& x1, const float& x2, const float& t)
{
	return x1 + (x2 - x1) * t;
}

template <typename T>
inline vec2f lerp(const vec2<T>& v1, const vec2<T>& v2, const float& t)
{
	return vec2f(v1.x + (v2.x - v1.x) * t, v1.y + (v2.y - v1.y) * t);
}
