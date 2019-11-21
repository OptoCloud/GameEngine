#include "object.h"

Object::Object(Object *parent)
{
	this->parent = parent;
	if (parent != nullptr)
	{
		std::scoped_lock lock(parent->mainMtx);
		parent->children.insert(std::pair<Object *, bool>(this, true));
	}
}

Object::~Object()
{
	std::scoped_lock lock(mainMtx);

	for (uint64_t i = children.size(); i > 0; i--)
	{
		if (children.begin()->second != false)
		{
			delete children.begin()->first;
		}
		children.erase(children.begin());
	}
	if (parent != nullptr)
	{
		parent->children.at(this) = false;
	}
}
