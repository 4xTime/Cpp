#pragma once
#ifndef H_VECTOR2D_H
#define H_VECTOR2D_H
struct Vector2{
	float x, y;
	template <typename T>
	constexpr Vector2(const T x = 0, const T y = 0) noexcept :x(x), y(y) {}
	
	constexpr const Vector2& operator-(const Vector2& arg)const noexcept {
		return Vector2(x - arg.x, y - arg.y);
	}

	constexpr const Vector2& operator+(const Vector2& arg)const noexcept {
		return Vector2(x + arg.x, y + arg.y);
	}	
	
	constexpr Vector2 operator/(const float factor) const noexcept {
		return Vector2{ x / factor, y / factor };
	}

	constexpr Vector2 operator*(const float factor) const noexcept {
		return Vector2{ x * factor, y * factor };
	}

	constexpr bool operator>(const Vector2& other) const noexcept {
		return x > other.x && y > other.y;
	}

	constexpr bool operator>=(const Vector2& other) const noexcept {
		return x >= other.x && y >= other.y;
	}

	constexpr bool operator<(const Vector2& other) const noexcept {
		return x < other.x&& y < other.y;
	}

	constexpr bool operator<=(const Vector2& other) const noexcept {
		return x <= other.x && y <= other.y;
	}
}; 
#endif
