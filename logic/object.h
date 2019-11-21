#ifndef OBJECT_H
#define OBJECT_H

#include <mutex>
#include <map>

/*
 Object class
 This Class keeps the program from having memory leaks
*/
class Object
{
public:
	/*
	 Class Constructor
	 Takes inn one parameter
	 If no parameter is passed, this object must be on the stack, and will delete all its children when it exits the scope
	 If a object is passed, the object will be the parent of this
	 The parent is responsible for deleting the child once the parent dies
	 If child dies, it will delete itseld inside the parent
	*/
	Object(Object* parent = nullptr);

	/*
	 Class Destructor
	*/
	~Object();

private:
	Object* parent = nullptr;			/* pointer to parent of this object */
	std::map<Object*, bool> children;	/* Children of this object */
	std::mutex mainMtx{};				/* Mutex for locking access to this thread for thread safety */
};

#endif // OBJECT_H
