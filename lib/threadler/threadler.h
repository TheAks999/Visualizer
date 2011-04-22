/************************************
*This file contains a simple, cross platform
*solution to multithreading
*
*
*Written by:
*  Alex Shepard
*  aksfkb@mst.edu
*************************************/
#ifndef THREADLER_H
#define THREADLER_H

#include "../singleton.h"

#ifdef WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

#include <vector>

#ifdef WIN32
typedef HANDLE ThreadHandle;
typedef DWORD WINAPI ThreadFxnType;
typedef LPVOID ThreadArgType;
#else
typedef pthread_t  ThreadHandle;
typedef void* ThreadFxnType;
typedef void* ThreadArgType;
#endif

typedef unsigned int ThreadID_t;

/**
  *This is a simple multi platform solution to threading
  *
  * Usage:
  1) make a new "main" function that is going to run the thread:

	ThreadFxnType fxnName(ThreadArgType threadArg)
	{
		//do stuff
		return (ThreadArgType)output;
	}

  2) create the thread within another thread, this starts the function going as well:
	Threadler::createThread(fxnName,args);

  + To wait for another thread to end use:
	Threadler::joinThread(fxnIndex);
  */
class Threadler : public Singleton<Threadler>
{
	public:
		static ThreadID_t createThread(ThreadFxnType fxn(ThreadArgType),ThreadArgType args);

		static ThreadHandle getThread(const ThreadID_t & index);
		static ThreadHandle getCurrentThread();

		static bool destroyThread(const ThreadID_t & index);
		static void exitThread(const int & exitVal);

		static bool snoozeThread(const ThreadID_t & index);
		static bool wakeThread(const ThreadID_t & index);

		static bool joinThread(const ThreadID_t & index);

	protected:
	/**
	  *
	  */
		std::vector<ThreadHandle> m_threads;
	private:
};

#endif // THREADLER_H
