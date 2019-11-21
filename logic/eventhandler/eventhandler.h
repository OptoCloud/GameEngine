#pragma once
#include <mutex>
#include <vector>
#include <thread>
#include <unordered_map>

#include "functors.h"

template <typename... Params>
class EventHandler
{
    // Disable copying of class
    EventHandler(const EventHandler&) = delete;
    EventHandler & operator=(const EventHandler&) = delete;
public:
    // Constructor & Destructor
	EventHandler():l_subscribers()
    {
    }
    ~EventHandler()
    {
        unsubscribeAll();
    }

    // Invoke all the member functions and static functions
	void trigger(const Params... params)
    {
		std::scoped_lock<std::mutex> lock(l_subscribers);
		for(Functor<Params...>* fn : m_subscribers)
			(*fn)(params...);
    }

    // Add a static function
    void subscribe(void (*function)(const Params...))
    {
		std::scoped_lock<std::mutex> lock(l_subscribers);
        StaticFunctor<Params...>* func = new StaticFunctor<Params...>(function);
		for(Functor<Params...>* fn : m_subscribers)
        {
            if (*fn == *func)
            {
                delete func;
                return;
            }
        }
		m_subscribers.push_back(func);
    }

    // Remove a static function
    void unsubscribe(void (*function)(const Params...))
    {
		std::scoped_lock<std::mutex> lock(l_subscribers);
        StaticFunctor func(function);
		for (auto i = m_subscribers.begin(); i != m_subscribers.end(); i++)
        {
            if (*(*i) == func)
            {
                delete *i;
				m_subscribers.erase(i);
                return;
            }
        }
    }

    // Add a member function
    template<class C>
    void subscribe(C* obj, void (C::*function)(const Params...))
    {
		std::scoped_lock<std::mutex> lock(l_subscribers);
        MemberFunctor<C, Params...>* func = new MemberFunctor<C, Params...>(function, obj);
		for(Functor<Params...>* fn : m_subscribers)
        {
            if (*fn == *func)
            {
                delete func;
                return;
            }
        }
		m_subscribers.push_back(func);
    }

    // Remove a member function
    template<class C>
    void unsubscribe(C* obj, void (C::*function)(const Params...))
    {
		std::scoped_lock<std::mutex> lock(l_subscribers);
        MemberFunctor<C> func(function, obj);
		for (auto i = m_subscribers.begin(); i != m_subscribers.end(); i++)
        {
            if (*(*i) == func)
            {
                delete *i;
				m_subscribers.erase(i);
                return;
            }
        }
    }

    // Remove all subscribers
    void unsubscribeAll()
    {
		std::scoped_lock<std::mutex> lock(l_subscribers);
		for(Functor<Params...>* fn : m_subscribers)
            delete fn;
		m_subscribers.clear();
    }

    // C# - Like subscription operator overload
    void operator += (void subscriber(const Params...))
    {
        subscribe(subscriber);
    }

    // C# - Like subscription operator overload
    void operator -= (void subscriber(const Params...))
    {
        unsubscribe(subscriber);
    }
private:
    // We dont want undefined behaviour
	std::mutex l_subscribers;

    // Vector for all the subscriber pointers
	std::vector<Functor<Params...>*> m_subscribers;
}; // Class EventHandler
