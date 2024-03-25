#include <cmath>

#include<headers/vector.h>

Vector::Vector(float p_x, float p_y)
	: x(p_x), y(p_y)
{
}

void Vector::SetX(float value)
{
	x = value;
}

void Vector::SetY(float value)
{
	y = value;
}

float Vector::GetX() const
{
	return x;
}

float Vector::GetY() const
{
	return y;
}

void Vector::SetAngle(float angle)
{
	float length = GetLength();
	x = std::cos(angle) * length;
	y = std::sin(angle) * length;
}

float Vector::GetAngle() const
{
	return std::atan2(y, x);
}

void Vector::SetLength(float len)
{
	float angle = GetAngle();
	x = std::cos(angle) * len;
	y = std::sin(angle) * len;
}

float Vector::GetLength() const
{
	return std::sqrt(x * x + y * y);
}

void Vector::AddTo(const Vector &v)
{
	x += v.x;
	y += v.y;
}