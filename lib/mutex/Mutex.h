#ifndef MUTEX_H
#define MUTEX_H

#include "../singleton.h"
#include <map>
#include <string>
#include <iostream>

#ifdef WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

//To keep things cleaner
#ifdef WIN32
typedef HANDLE MutexHandle;
#else
typedef pthread_mutex_t MutexHandle;
#endif

typedef std::string MutexID_t;

/**
  *This class is a multiplatform solution to mutexes
  *
  * usage:
	1) create a mutex for the specific problem using:
		Mutex::createMutex(mutexName);
		this is true if it worked

	2) to lock a section of code use
		Mutex::lock(mutexName);

	3) to unlock use:
		Mutex::unlock(mutexName);
  */
class Mutex : public Singleton<Mutex>
{
public:
    static bool createMutex(const MutexID_t & mutexName);
    static bool lock(const MutexID_t & mutexName);
    static bool unlock(const MutexID_t & mutexName);
    static bool mutexExists(const MutexID_t & mutexName);

    //Warning: only use this when qualifying with #ifdef SYSTEM_NAME
    static MutexHandle getMutex(const MutexID_t & mutexName);


protected:
    std::map<MutexID_t,MutexHandle> m_mutexes;

private:
};

#endif // MUTEX_H
