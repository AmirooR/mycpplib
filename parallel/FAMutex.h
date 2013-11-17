#ifndef __FA_MUTEX_H_
#define __FA_MUTEX_H_

#include <pthread.h>

class FAMutex
{
	private:
	pthread_mutex_t mutex;
	public:
	FAMutex()
	{
		pthread_mutex_init(&mutex,NULL);
	}
	void lock()
	{
		pthread_mutex_lock(&mutex);
	}

	void unlock()
	{
		pthread_mutex_unlock(&mutex);
	}
};

#endif
