/*#include "net/CURLHTTPManager.h"
#include "parallel/FAThread.h"
#include "control/IRule.h"

#include <sstream>
#include <iostream>
#include <string>

using namespace std;*/

#include "net/ParallelHttpRequester.h"

class CerrIRule: public IRule
{
protected:
	string pattern;
public:
	bool matches(string pattern){this->pattern = pattern;return true;}
	void doAction(){cerr<<pattern<<" ";}
};


class IDParaHttpRequester:public ParallelHttpRequester
{
	int x;
public:
	IDParaHttpRequester(string url, HTTPManager* http_manager,bool timed = false, useconds_t step = 1000, bool conditioned = false):ParallelHttpRequester(url,http_manager, timed, step, conditioned)
	{
		x = 0;
	}

	void action()
	{
		stringstream s;
		s<<"?id="<<x++;
		string lastUrl = url;
		url += s.str();
		ParallelHttpRequester::action();
		url = lastUrl;
	}
};

int main()
{
	HTTPManager *h1 = new CURLHTTPManager();
	HTTPManager *h2 = new CURLHTTPManager(true,"amir","amir");
	ParallelHttpRequester* p1 = new IDParaHttpRequester("http://localhost/~amirrahimi/salam.php",h1,true, 100000);
	ParallelHttpRequester* p2 = new IDParaHttpRequester("http://localhost2/~amirrahimi/khodafez.php",h2,true, 1000000);
	usleep(1000*1000);
	CerrIRule r1;
	p1->setIRule(&r1);
	p2->setIRule(&r1);
	p1->start();
	p2->start();
	usleep(5 * 1000 * 1000);
	p1->stop();
	p1->join();
	delete p1;
	usleep(3 * 1000 * 1000);
	p2->stop();
	p2->join();
	//usleep(200000);
	delete p2;
	delete h1;
	delete h2;
	return 0;
}
