#ifndef __IRULE_H
#define __IRULE_H

#include <string>

using namespace std;

class IRule
{
public:
	virtual bool matches(string pattern) = 0;
	virtual void doAction(){}
};

#endif
