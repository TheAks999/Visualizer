#include "Mutex.h"


/** @brief getMutex
  * get a handle to a mutex
  * @param mutexName the name of the mutex
  * @return a handle to the mutex
  */
MutexHandle Mutex::getMutex(const MutexID_t & mutexName)
{
	if (!isInit())
	{
		std::cout << "Attempting to get a mutex with an uninitialized singleton\n";
		return MutexHandle();
	}

	if (get()->m_mutexes.find(mutexName) != get()->m_mutexes.end())
	{
		return get()->m_mutexes[mutexName];
	}

	std::cout <<"\"" << mutexName << "\" is not a valid mutex\n";
	return MutexHandle();
}

/** @brief unlock
  * unlock an existing mutex
  * @param mutexName the name of the mutex to unlock
  * @return true if the lock was successfully released
  */
bool Mutex::unlock(const MutexID_t & mutexName)
{
	if (!isInit())
	{
		std::cout << "Attempting to unlock a mutex with an uninitialized singleton\n";
		return false;
	}
	if (get()->m_mutexes.find(mutexName) != get()->m_mutexes.end())
	{
		#ifdef WIN32
		ReleaseMutex(get()->m_mutexes[mutexName]);
		#else
		pthread_mutex_unlock(&get()->m_mutexes[mutexName]);
		#endif
		return true;
	}

	std::cout <<"\"" << mutexName << "\" is not a valid mutex\n";
	return false;
}

/** @brief lock
  * lock an existing mutex
  * @param mutexName the name of the mutex to lock
  * @return true if the lock was successfully grabbed
  */
bool Mutex::lock(const MutexID_t & mutexName)
{
    if (!isInit())
	{
		std::cout << "Attempting to lock a mutex with an uninitialized singleton\n";
		return false;
	}

	if (get()->m_mutexes.find(mutexName) != get()->m_mutexes.end())
	{
		#ifdef WIN32
		WaitForSingleObject(get()->m_mutexes[mutexName],INFINITE);
		#else
		pthread_mutex_lock(&(get()->m_mutexes[mutexName]));
		#endif
		return true;
	}

	std::cout <<"\"" << mutexName << "\" is not a valid mutex\n";
	return false;
}


/** @brief createMutex
  * create a mutex
  * @param mutexName the name of the mutex to create
  * @return true if the creation was successful
  */
bool Mutex::createMutex(const MutexID_t & mutexName)
{
	if (!isInit())
	{
		std::cout << "Attempting to create a mutex with an uninitialized singleton\n";
		return false;
	}
	if (get()->m_mutexes.find(mutexName) == get()->m_mutexes.end())
	{
		#ifdef WIN32
		get()->m_mutexes[mutexName] = CreateMutex(NULL,false,NULL);
		#else
		pthread_mutex_t temp = PTHREAD_MUTEX_INITIALIZER;
		get()->m_mutexes[mutexName] = temp;
		#endif
		return true;
	}

	std::cout <<"\"" << mutexName << "\" already exists\n";
	return false;
}


