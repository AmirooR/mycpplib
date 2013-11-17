#ifndef __FA_THREAD_H_
#define __FA_THREAD_H_

#include <pthread.h>
#include <unistd.h>
#include <iostream>

using namespace std;
//TODO: fix for windows

class FAThread
{
	private:
	pthread_t thread_id;
	static void* doRun(void *f)
	{
		FAThread* d = (FAThread*)f;
		d->run();
	}

	protected:
	bool isBusy;
	public:
	
	FAThread()
	{
		isBusy = false;
	}

	bool am_I_Busy()
	{
		return isBusy;
	}
	void start()
	{
		isBusy = true;
		pthread_create(&thread_id,NULL,&doRun,this);
	}

	void join()
	{
		pthread_join(thread_id,NULL);
		isBusy = false;
	}

	void cancel()
	{
		if( isBusy )
		{
			pthread_cancel(thread_id);
			isBusy = false;
		}
	}
	virtual void run(){}
};


class ConditionalLoopThread: public FAThread
{
protected:
	bool stopMe;
	bool timed;
	useconds_t step;
	bool conditioned;
	bool allowme;
	
public:
	ConditionalLoopThread(bool timed = false, useconds_t step = 1000, bool conditioned = false):FAThread(),stopMe(false),timed(timed),step(step),conditioned(conditioned),allowme(false){}

	virtual void before(){}
	virtual void action(){}
	virtual void after(){}

	void setConditioned(bool conditioned){this->conditioned = conditioned;}
	void setStep( useconds_t step){this->step = step;}
	void setTimed( bool timed){this->timed = timed;}
	
	bool isStoped(){return stopMe;}
	bool isConditioned(){return conditioned;}
	bool isTimed(){return timed;}
	useconds_t getTimeStep(){return step;}

	void run()
	{
		before();
		while(!stopMe)
		{
			if(!conditioned)
				action();
			else if ( allowme )
			{
				action();
				allowme = false;
			}
			if(timed) { usleep(step);}
		}
		after();
	}

	void stop()
	{
		stopMe = true;
		isBusy = false;
	}

	void allow()
	{
		allowme = true;
	}
};

typedef class ConditionalLoopThread CLThread;

#endif
