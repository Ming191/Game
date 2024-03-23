#pragma once

class Vector
{
public:
	Vector() = default;
	Vector(float p_x, float p_y);

	float GetX() const;
	void SetX(float value);

	float GetY() const;
	void SetY(float value);

	float GetAngle() const;
	void SetAngle(float angle);

	float GetLength() const;
	void SetLength(float len);

private:
	float x = 0.f;
	float y = 0.f;
};