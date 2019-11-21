#include "types.h"

Vector2::Vector2()
{
}
Vector2::Vector2(const Vector2& other)
{
	this->x = other.x;
	this->y = other.y;
}
Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}
Vector2::Vector2(double x, double y)
{
	this->x = static_cast<float>(x);
	this->y = static_cast<float>(y);
}
Vector2::Vector2(Vector2L v)
{
	this->x = static_cast<float>(v.x);
	this->y = static_cast<float>(v.y);
}
Vector2::~Vector2()
{
}

Vector2L::Vector2L()
{
}
Vector2L::Vector2L(const Vector2L& other)
{
	this->x = other.x;
	this->y = other.y;
}
Vector2L::Vector2L(float x, float y)
{
	this->x = x;
	this->y = y;
}
Vector2L::Vector2L(double x, double y)
{
	this->x = x;
	this->y = y;
}
Vector2L::Vector2L(Vector2 v)
{
	this->x = v.x;
	this->y = v.y;
}
Vector2L::~Vector2L()
{
}
