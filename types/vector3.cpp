#include "types.h"

Vector3::Vector3()
{
}
Vector3::Vector3(const Vector3& other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}
Vector3::Vector3(float  x, float  y, float  z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
Vector3::Vector3(double x, double y, double z)
{
	this->x = static_cast<float>(x);
	this->y = static_cast<float>(y);
	this->z = static_cast<float>(z);
}
Vector3::Vector3(Vector2 v, float   z)
{
	this->x = v.x;
	this->y = v.y;
	this->z = z;
}
Vector3::Vector3(float   x, Vector2 v)
{
	this->x = x;
	this->y = v.x;
	this->z = v.y;
}
Vector3::Vector3(Vector2L v, double   z)
{
	this->x = static_cast<float>(v.x);
	this->y = static_cast<float>(v.y);
	this->z = static_cast<float>(z);
}
Vector3::Vector3(double   x, Vector2L v)
{
	this->x = static_cast<float>(x);
	this->y = static_cast<float>(v.x);
	this->z = static_cast<float>(v.y);
}
Vector3::Vector3(Vector3L v)
{
	this->x = static_cast<float>(v.x);
	this->y = static_cast<float>(v.y);
	this->z = static_cast<float>(v.z);
}
Vector3::~Vector3()
{
}

Vector3L::Vector3L()
{
}
Vector3L::Vector3L(const Vector3L& other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}
Vector3L::Vector3L(float  x, float  y, float  z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
Vector3L::Vector3L(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
Vector3L::Vector3L(Vector2 v, float   z)
{
	this->x = v.x;
	this->y = v.y;
	this->z = z;
}
Vector3L::Vector3L(float   x, Vector2 v)
{
	this->x = x;
	this->y = v.x;
	this->z = v.y;
}
Vector3L::Vector3L(Vector2L v, double   z)
{
	this->x = v.x;
	this->y = v.y;
	this->z = z;
}
Vector3L::Vector3L(double   x, Vector2L v)
{
	this->x = x;
	this->y = v.x;
	this->z = v.y;
}
Vector3L::Vector3L(Vector3 v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}
Vector3L::~Vector3L()
{
}
