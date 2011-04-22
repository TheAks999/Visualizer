/************************************
*This file contains a templated
*singleton class.
*
*
*Written by:
*  Alex Shepard
*  aksfkb@mst.edu
*************************************/

#ifndef SINGLETON_H
#define SINGLETON_H
#include <cstdlib>
#ifdef DEBUG
#include <iostream>
#endif


/**
  * To use it you place
  *all of your member variables into a
  *non-singleton class and then
  *inherit from this singleton class
  *with the first class as the template
  *parameter. Use the create() and destroy()
  *functions to make your class. Use isInit()
  *for safety. The function get() returns
  *a pointer to the templated class and
  *will return NULL if create() has not
  *been called.

	Example 1:

	class MyClass1
	{
		public: int m_intVar;
	};
	class MySingleton1 : public Singleton <MyClass1>
	{
		public:
		int intAccessor()
		{
			if (isInit())
			{
				return get()->m_intVar;
			}
			return 0;
		}
	};

	Example 2:
	class MySingleton2<MySingleton2>
	{
		m_intVar;
		public:
		int intAccessor()
		{
			if (isInit())
			{
				return get()->m_intVar;
			}
			return 0;
		}
	};
};
  */
template<class T>
class Singleton
{
    public:
		/**
		  *Create the instance of a singleton
		  *@return true if no other intsance of this singleton exists
		  */
        static bool create()
        {
            if (m_isInit)
            return false;

            m_base = new T;
            m_isInit = true;
            return true;
        }

		/**
		  *Destroy the instance of a singleton
		  *@return true if the singleton was created
		  */
        static bool destroy()
        {
            if (!m_isInit)
		return false;

            delete m_base;
            m_base = NULL;
            m_isInit = false;
            return true;
        }


		/**
		  *Check if a singleton has been created
		  *@return true if an instance exists
		  */
        static bool isInit()
        {
            return m_isInit;
        }
    protected:
		/**
		  *Get the instance of the singleton
		  *@return a pointer to the singleton's templated object if created, or
		  * NULL if not created
		  */
        static inline T * get()
        {
            #ifdef DEBUG
                if (!m_isInit)
                {
                    std::cout << "Accessing an uninitialized singleton!\n";
                    return NULL;
                }
            #endif
            return m_base;
        }

    protected:
		/**
		  *The instance of the singleton
		  */
        static T * m_base;
		/**
		  *Stores if the singleton has been created
		  */
        static bool m_isInit;
};


//initialization stuff, doesn't need to be touched
template <class T>
T * Singleton<T>::m_base = NULL;

template <class T>
bool Singleton<T>::m_isInit = false;


#endif // SINGLETON_H
