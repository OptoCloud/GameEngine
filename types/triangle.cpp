#include "types.h"
#include <algorithm>

Triangle::Triangle()
{
}
Triangle::Triangle(const Triangle& other)
{
	vertices[0] = other.vertices[0];
	vertices[1] = other.vertices[1];
	vertices[2] = other.vertices[2];
}
Triangle::Triangle(Vertex v1, Vertex v2, Vertex v3)
{
	vertices[0] = v1;
	vertices[1] = v2;
	vertices[2] = v3;
}
Triangle::~Triangle()
{

}

void Triangle::Flip() noexcept
{
	std::swap(vertices[1], vertices[2]);
}