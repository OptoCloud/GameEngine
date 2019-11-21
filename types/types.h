#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <inttypes.h>

// Predefine
struct Vector2;
struct Vector2L;
struct Vector2;
struct Vector3L;
struct Vector4;
struct Vector4L;

struct ColorRgba;
struct Vertex;

struct Quaternion;

struct Triangle;
struct Bitmap;
struct Animation;

struct Mesh;
struct Bone;

struct Vector2
{
	Vector2();
	Vector2(const Vector2& other);

	Vector2(float x, float y);
	Vector2(double x, double y);

	Vector2(Vector2L v);
	~Vector2();

	float x = 0.f;
	float y = 0.f;

	Vector2& Scale(Vector2 factor);
	Vector2& Scale(Vector2L factor);
};
struct Vector2L
{
	Vector2L();
	Vector2L(const Vector2L& other);

	Vector2L(float x, float y);
	Vector2L(double x, double y);

	Vector2L(Vector2 v);
	~Vector2L();

	double x = 0.;
	double y = 0.;

	void Scale(Vector2 factor);
	void Scale(Vector2L factor);
};
struct Vector3
{
	Vector3();
	Vector3(const Vector3 &other);

	Vector3(float x, float y, float z);
	Vector3(double x, double y, double z);

	Vector3(Vector2 v, float   z);
	Vector3(float   x, Vector2 v);

	Vector3(Vector2L v, double   z);
	Vector3(double   x, Vector2L v);

	Vector3(Vector3L v);
	~Vector3();

	float x = 0.f;
	float y = 0.f;
	float z = 0.f;
};
struct Vector3L
{
	Vector3L();
	Vector3L(const Vector3L& other);

	Vector3L(float  x, float  y, float  z);
	Vector3L(double x, double y, double z);

	Vector3L(Vector2 v, float   z);
	Vector3L(float   x, Vector2 v);

	Vector3L(Vector2L v, double   z);
	Vector3L(double   x, Vector2L v);

	Vector3L(Vector3 v);
	~Vector3L();

	double x = 0.;
	double y = 0.;
	double z = 0.;
};
struct Vector4
{
	Vector4();
	Vector4(const Vector4& other);
	Vector4(float  x, float  y, float  z, float  w);
	Vector4(double x, double y, double z, double w);
	Vector4(Vector2 v, float   z, float   w);
	Vector4(float   x, Vector2 v, float   w);
	Vector4(float   x, float   y, Vector2 v);
	Vector4(Vector3 v, float   w);
	Vector4(float   x, Vector3 v);
	Vector4(Vector2 v1, Vector2 v2);
	Vector4(Vector2L v, double   z, double   w);
	Vector4(double   x, Vector2L v, double   w);
	Vector4(double   x, double   y, Vector2L v);
	Vector4(Vector3L v, double   w);
	Vector4(double   x, Vector3L v);
	Vector4(Vector2L v1, Vector2L v2);
	Vector4(Vector4L v);
	~Vector4();

	float x = 0.f;
	float y = 0.f;
	float z = 0.f;
	float w = 0.f;
};
struct Vector4L
{
	Vector4L();
	Vector4L(const Vector4L& other);
	Vector4L(float  x, float  y, float  z, float  w);
	Vector4L(double x, double y, double z, double w);
	Vector4L(Vector2 v, float   z, float   w);
	Vector4L(float   x, Vector2 v, float   w);
	Vector4L(float   x, float   y, Vector2 v);
	Vector4L(Vector3 v, float   w);
	Vector4L(float   x, Vector3 v);
	Vector4L(Vector2 v1, Vector2 v2);
	Vector4L(Vector2L v, double   z, double   w);
	Vector4L(double   x, Vector2L v, double   w);
	Vector4L(double   x, double   y, Vector2L v);
	Vector4L(Vector3L v, double   w);
	Vector4L(double   x, Vector3L v);
	Vector4L(Vector2L v1, Vector2L v2);
	Vector4L(Vector4 v);
	~Vector4L();

	double x = 0.;
	double y = 0.;
	double z = 0.;
	double w = 0.;
};

struct ColorRgba
{
	ColorRgba();
	ColorRgba(const ColorRgba& other);
	~ColorRgba();

	uint8_t r = 0;
	uint8_t g = 0;
	uint8_t b = 0;
	uint8_t a = 0;
};
struct Vertex
{
	Vertex();
	Vertex(const Vertex& other);
	~Vertex();

	Vector3 position;
	Vector3 normal;
	ColorRgba color;
	Vector2 uv;
};

struct Quaternion
{
	Quaternion();
	Quaternion(const Quaternion &other);
	~Quaternion();

	float x = 0.;
	float y = 0.;
	float z = 0.;
	float w = 0.;
};

struct Triangle
{
	Triangle();
	Triangle(const Triangle& poly);
	Triangle(Vertex v1, Vertex v2, Vertex v3);
	~Triangle();

	void Flip() noexcept;

	Vertex vertices[3];
};
struct Bitmap
{
	Bitmap();
	Bitmap(const Bitmap &other);
	~Bitmap();

	static Bitmap* LoadFile(const char* fileName);

	ColorRgba** data = nullptr;
	uint16_t height = 0;
	uint16_t width = 0;
};
struct Animation
{
	Animation();
	Animation(const Animation &other);
	~Animation();

	Bitmap* frames = nullptr;
	uint32_t nFrames = 0;
	uint32_t frameTimeInUs = 0;
};

struct Mesh
{
	Mesh();
	Mesh(const Mesh& other);
	~Mesh();

	Triangle* polygons;
	uint32_t nPolygons;
};
struct Bone
{
	Bone();
	Bone(const Bone& other);
	~Bone();
};

#endif
