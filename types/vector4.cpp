#include "types.h"

Vector4::Vector4()
{
}
Vector4::Vector4(const Vector4& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
}
Vector4::Vector4(float  x, float  y, float  z, float  w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}
Vector4::Vector4(double x, double y, double z, double w)
{
	this->x = static_cast<float>(x);
	this->y = static_cast<float>(y);
	this->z = static_cast<float>(z);
	this->w = static_cast<float>(w);
}
Vector4::Vector4(Vector2 v, float   z, float   w)
{
	this->x = v.x;
	this->y = v.y;
	this->z = z;
	this->w = w;
}
Vector4::Vector4(float   x, Vector2 v, float   w)
{
	this->x = x;
	this->y = v.x;
	this->z = v.y;
	this->w = w;
}
Vector4::Vector4(float   x, float   y, Vector2 v)
{
	this->x = x;
	this->y = y;
	this->z = v.x;
	this->w = v.y;
}
Vector4::Vector4(Vector3 v, float   w)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	this->w = w;
}
Vector4::Vector4(float   x, Vector3 v)
{
	this->x = x;
	this->y = v.x;
	this->z = v.y;
	this->w = v.z;
}
Vector4::Vector4(Vector2 v1, Vector2 v2)
{
	this->x = v1.x;
	this->y = v1.y;
	this->z = v2.x;
	this->w = v2.y;
}
Vector4::Vector4(Vector2L v, double   z, double   w)
{
	this->x = static_cast<float>(v.x);
	this->y = static_cast<float>(v.y);
	this->z = static_cast<float>(z);
	this->w = static_cast<float>(w);
}
Vector4::Vector4(double   x, Vector2L v, double   w)
{
	this->x = static_cast<float>(x);
	this->y = static_cast<float>(v.x);
	this->z = static_cast<float>(v.y);
	this->w = static_cast<float>(w);
}
Vector4::Vector4(double   x, double   y, Vector2L v)
{
	this->x = static_cast<float>(x);
	this->y = static_cast<float>(y);
	this->z = static_cast<float>(v.x);
	this->w = static_cast<float>(v.y);
}
Vector4::Vector4(Vector3L v, double   w)
{
	this->x = static_cast<float>(v.x);
	this->y = static_cast<float>(v.y);
	this->z = static_cast<float>(v.z);
	this->w = static_cast<float>(w);
}
Vector4::Vector4(double   x, Vector3L v)
{
	this->x = static_cast<float>(x);
	this->y = static_cast<float>(v.x);
	this->z = static_cast<float>(v.y);
	this->w = static_cast<float>(v.z);
}
Vector4::Vector4(Vector2L v1, Vector2L v2)
{
	this->x = static_cast<float>(v1.x);
	this->y = static_cast<float>(v1.y);
	this->z = static_cast<float>(v2.x);
	this->w = static_cast<float>(v2.y);
}
Vector4::Vector4(Vector4L v)
{
	this->x = static_cast<float>(v.x);
	this->y = static_cast<float>(v.y);
	this->z = static_cast<float>(v.z);
	this->w = static_cast<float>(v.w);
}
Vector4::~Vector4()
{
}

Vector4L::Vector4L()
{
}
Vector4L::Vector4L(const Vector4L& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
}
Vector4L::Vector4L(float  x, float  y, float  z, float  w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}
Vector4L::Vector4L(double x, double y, double z, double w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}
Vector4L::Vector4L(Vector2 v, float   z, float   w)
{
	this->x = v.x;
	this->y = v.y;
	this->z = z;
	this->w = w;
}
Vector4L::Vector4L(float   x, Vector2 v, float   w)
{
	this->x = x;
	this->y = v.x;
	this->z = v.y;
	this->w = w;
}
Vector4L::Vector4L(float   x, float   y, Vector2 v)
{
	this->x = x;
	this->y = y;
	this->z = v.x;
	this->w = v.y;
}
Vector4L::Vector4L(Vector3 v, float   w)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	this->w = w;
}
Vector4L::Vector4L(float   x, Vector3 v)
{
	this->x = x;
	this->y = v.x;
	this->z = v.y;
	this->w = v.z;
}
Vector4L::Vector4L(Vector2 v1, Vector2 v2)
{
	this->x = v1.x;
	this->y = v1.y;
	this->z = v2.x;
	this->w = v2.y;
}
Vector4L::Vector4L(Vector2L v, double   z, double   w)
{
	this->x = v.x;
	this->y = v.y;
	this->z = z;
	this->w = w;
}
Vector4L::Vector4L(double   x, Vector2L v, double   w)
{
	this->x = x;
	this->y = v.x;
	this->z = v.y;
	this->w = w;
}
Vector4L::Vector4L(double   x, double   y, Vector2L v)
{
	this->x = x;
	this->y = y;
	this->z = v.x;
	this->w = v.y;
}
Vector4L::Vector4L(Vector3L v, double   w)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	this->w = w;
}
Vector4L::Vector4L(double   x, Vector3L v)
{
	this->x = x;
	this->y = v.x;
	this->z = v.y;
	this->w = v.z;
}
Vector4L::Vector4L(Vector2L v1, Vector2L v2)
{
	this->x = v1.x;
	this->y = v1.y;
	this->z = v2.x;
	this->w = v2.y;
}
Vector4L::Vector4L(Vector4 v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	this->w = v.w;
}
Vector4L::~Vector4L()
{
}