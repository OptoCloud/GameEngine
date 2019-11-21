#pragma once
#include <mutex>
#include <vector>
#include <thread>
#include <unordered_map>

#include "fastdebug.h" // @DEBUG

#include "functors.h"
#include "eventhandler.h"

template <typename Key, typename... Params>
class CallbackHandler
{
    // Disable copying of class
    CallbackHandler(const CallbackHandler& other) = delete;
    CallbackHandler& operator = (const CallbackHandler& other) = delete;
public:
    // Constructor & Destructor
	CallbackHandler():l_requests()
    {
        FASTDEBUG_CLASS("Constructed");
    }
    ~CallbackHandler()
    {
        FASTDEBUG_CLASS("Deconstructed");
        removeAllRequests();
    }

    EventHandler<Key> onRequest;

    // Send out the reponse to all the requesters
    void respond(Key key, const Params... params)
    {
		std::scoped_lock<std::mutex> lock(l_requests);
		for (auto i = m_requests.begin(); i != m_requests.end(); i++)
        {
            if (i->first == key)
            {
                (*(i->second))(params...);
				m_requests.erase(i);
            }
        }
    }

    // Add a static function assigned to this request
    void request(Key key, void (*function)(const Params...))
    {
		std::scoped_lock<std::mutex> lock(l_requests);
        StaticFunctor<Params...>* func = new StaticFunctor(function);
		for (auto i = m_requests.begin(); i != m_requests.end(); i++)
        {
            if (i->first == key && *(i->second) == *func)
            {
                delete func;
                return;
            }
        }
		m_requests.insert(std::pair<Key, Functor<Params...>*>(key, func));
        onRequest.trigger(key);
    }

    // Remove a static function
    void removeRequest(Key key, void (*function)(const Params...))
    {
		std::scoped_lock<std::mutex> lock(l_requests);
        StaticFunctor func(function);
		for (auto i = m_requests.begin(); i != m_requests.end(); i++)
        {
            if (i->first == key && *(i->second) == func)
            {
                delete i.second;
				m_requests.erase(i);
                return;
            }
        }
    }

    // Add a member function
    template<class C>
    void request(Key key, C* obj, void (C::*function)(const Params...))
    {
		std::scoped_lock<std::mutex> lock(l_requests);
        MemberFunctor<C>* func = new MemberFunctor<C>(function, obj);
		for (auto i = m_requests.begin(); i != m_requests.end(); i++)
        {
            if (i->first == key && *(i->second) == *func)
            {
                delete func;
                return;
            }
        }
		m_requests.insert(std::pair<Key, Functor<Params...>*>(key, func));
        onRequest.trigger(key);
    }

    // Remove a member function
    template<class C>
    void removeRequest(Key key, C* obj, void (C::*function)(const Params...))
    {
		std::scoped_lock<std::mutex> lock(l_requests);
        MemberFunctor<C> func(function, obj);
		for (auto i = m_requests.begin(); i != m_requests.end(); i++)
        {
            if (i->first == key && *(i->second) == func)
            {
                delete i.second;
				m_requests.erase(i);
                return;
            }
        }
    }

    // Remove all subscribers
    void removeAllRequests()
    {
		std::scoped_lock<std::mutex> lock(l_requests);
		for (auto i = m_requests.begin(); i != m_requests.end(); i++)
        {
            delete i->second;
        }
		m_requests.clear();
    }
private:
	std::mutex l_requests;
	std::unordered_map<Key, Functor<Params...>*> m_requests;
}; // class CallbackHandler
