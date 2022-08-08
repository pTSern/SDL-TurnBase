#pragma once
#include "Vector2D.h"

class Transform
{
public:
	float X, Y;
	Transform(float x, float y): X(x), Y(y) {};
	void Log()
	{
		std::cout << X << " : " << Y;
	}
	inline void SetX(float x)
	{
		X = x;
	}
	inline void SetY(float y)
	{
		Y = y;
	}
	inline void TranslateX(float x)
	{
		X += x;
	}
	inline void TranslateY(float y)
	{
		Y += y;
	}
	inline void TranslateVec(Vector2D vec)
	{
		X += vec.getX();
		Y += vec.getY();
	}
};