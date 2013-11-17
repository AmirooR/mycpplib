#include "parallel/FAThread.h"
#include "parallel/FAMutex.h"

#include <iostream>

using namespace std;

int x = 0;

class ThreadRunner: public FAThread
{
	bool minus;
	FAMutex* m;
public:
	ThreadRunner(bool minus, FAMutex* m):FAThread(),minus(minus),m(m)
	{
	}

	void run()
	{
//		m->lock();
		for(int i = 0; ; i++)
		{
			if( minus )
			{
				cout<< -i << " ";
			}
			else
			{
				cout<< i << " ";
			}

			/*if( minus && i > 500)
			{
				return;
			}*/
			x++;
		}
		cout<<endl;
//		m->unlock();
	}
};

class CLThreadRunner:public ConditionalLoopThread
{
	int i;
	public:
	CLThreadRunner(bool timed = false, useconds_t step = 1000):ConditionalLoopThread(timed, step)
	{
		i = 0;
	}
	/*void run()
	{
		ConditionalLoopThread::run();
	}*/
	void action()
	{
		cerr<< ++i << " ";
	}

	int getI()
	{
		return i;
	}
};


int testThreadRunner()
{
	FAMutex m;
	ThreadRunner r1(true, &m), r2(false, &m);
	r1.start();
	r2.start();
	while(true)//r1.am_I_Busy() && r2.am_I_Busy())
	{
		if( x > 50 )
		{
			r1.cancel();
		}
	}
	//r1.join();
	//r2.join();
	cout<<"Goodbye"<<endl;
	return 0;
}

int testCLThreadRunner()
{
	CLThreadRunner* r1 = new CLThreadRunner(true,100000);
	cout<<"(before start) R1 running? "<<r1->am_I_Busy()<<endl;
	r1->start();
	cout<<"(after start) R1 running? "<<r1->am_I_Busy()<<endl;
	while(true)
	{
		if(r1->getI() > 10)
		{
			r1->stop();
			break;
		}
	}
	//r1->join();
	cout<<"(after stop) R1 running? "<<r1->am_I_Busy()<<endl;
	return 0;
}

int main()
{
	//testThreadRunner();
	testCLThreadRunner();
	return 0;
}
