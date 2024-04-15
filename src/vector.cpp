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

void Vector::AddTo(const Vector &v)
{
	x += v.x;
	y += v.y;
}