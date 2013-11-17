#ifndef _PARA_HTTP_REQER_
#define _PARA_HTTP_REQER_

#include "net/CURLHTTPManager.h"
#include "parallel/FAThread.h"
#include "control/IRule.h"

#include <sstream>
#include <iostream>
#include <string>

using namespace std;

class ParallelHttpRequester: public CLThread
{
protected:
	HTTPManager* http_manager;
	string url;
	struct MemoryStruct chunk;
	IRule* r;
	bool hasIRule;
public:
	ParallelHttpRequester(string url, HTTPManager* http_manager,bool timed = false, useconds_t step = 1000, bool conditioned = false):CLThread(timed,step,conditioned),url(url), http_manager(http_manager)
	{
		hasIRule = false;
	}

	void setIRule(IRule* r)
	{
		this->r = r;
		hasIRule = true;
	}

	void action()
	{
		chunk.size = 0;
		chunk.memory = NULL;
		chunk = http_manager->sendQuery(url);
		if(chunk.size > 0)
		{
			string str(chunk.memory,chunk.size);
			if( hasIRule)
			{
				if(r->matches(str))
				{
					r->doAction();
				}
			}
			free(chunk.memory);
		}
	}

	void setUrl(string url)
	{
		this->url = url;
	}

	~ParallelHttpRequester(){}
};

#endif
