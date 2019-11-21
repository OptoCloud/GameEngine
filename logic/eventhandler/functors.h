#pragma once
#include <mutex>
#include <vector>
#include <thread>
#include <unordered_map>

// Forward declaration of Functor class
template <typename... Params>
class Functor;

// MemberFunctor class to holder member pointers
template <class C, typename... Params>
class MemberFunctor : public Functor<Params...>
{
    friend class Functor<Params...>;

    MemberFunctor() = delete; /**< @brief Delete default constructor */
    MemberFunctor(const MemberFunctor& other) = delete; /**< @brief Delete copy constructor */
    MemberFunctor& operator = (const MemberFunctor& tmp_obj) = delete; /**< @brief Delete copy operator */
public:
    MemberFunctor(void(C::*function)(const Params... params), C* obj) : Functor<Params...> (true) /**< @brief Constructor, takes in a functionpointer to a class member function */
    {
		m_function = function;
		m_object = obj;
	}

    void operator () (const Params... params) const /**< @brief Invokes internal functionpointer */
    {
		((*m_object).*m_function)(params...);
    }
private:
	void (C::*m_function)(const Params...); /**< @brief Functionpointer */
	C *m_object; /**< @brief Object for pointer */
};

// StaticFunctor class to hold static pointers
template <typename... Params>
class StaticFunctor : public Functor<Params...>
{
    friend class Functor<Params...>;

    StaticFunctor() = delete; /**< @brief Delete default constructor */
    StaticFunctor(const StaticFunctor& other) = delete; /**< @brief Delete copy constructor */
    StaticFunctor& operator = (const StaticFunctor& tmp_obj) = delete; /**< @brief Delete copy operator */
public:
    StaticFunctor(void(*function)(const Params...)) : Functor<Params...> (false) /**< @brief Constructor, takes in a functionpointer */
    {
		m_function = function;
	}

    void operator () (const Params... params) const /**< @brief Invokes internal functionpointer */
    {
		m_function(params...);
    }
private:
	void(*m_function)(const Params...); /**< @brief Functionpointer */
};

// Functor interface to inherit onto StaticFunctor and MemberFunctor which will hold function and member pointers
template <typename... Params>
class Functor
{
protected:
    Functor() = delete;
    Functor(bool isMember)
    {
		m_isMember = isMember;
    }
    Functor(const Functor& other) = delete;
    Functor& operator = (const Functor& tmp_obj) = delete;
	bool m_isMember = false;
public:
    virtual void operator()(const Params... params) const = 0;
	bool isMember() const { return m_isMember; }

    // Operator to determine if Inherited class is a StaticAction class that matches using dynamic casting
    bool operator == (const StaticFunctor<Params...> &other)
    {
		return other.m_isMember ?
                    false
                  :
					reinterpret_cast<StaticFunctor<Params...>*>(this)->m_function == other.m_function ?
                        true
                      :
                        false;
    }

    // Operator to determine if Inherited class is a StaticAction class that matches using dynamic casting
    template <class C>
    bool operator == (const MemberFunctor<C, Params...> &other)
    {
		return other.m_isMember ?
					reinterpret_cast<MemberFunctor<C, Params...>*>(this)->m_object == other.m_object &&
					reinterpret_cast<MemberFunctor<C, Params...>*>(this)->m_function == other.m_function ?
                        true
                      :
                        false
                  :
                    false;
    }
};
