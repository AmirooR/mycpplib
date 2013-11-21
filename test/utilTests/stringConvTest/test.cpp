#include <string>
#include <sstream>
#include <iostream>
#include <exception>
#include <csignal>
#include <stdlib.h>

using namespace std;

struct ValueErrorException: public exception
{
//public:
//	string str;
//public:
	
//	ValueErrorException():exception(){str = "";}
	
/*	ValueErrorException(string str):exception(), str(str)
	{
	}
	
	ValueErrorException(const char* str):exception(), str(str)
	{
	}

	~ValueErrorException() throw() {}
*/
//private:
	const char* what() const throw()
	{
		//string err = "Value error: ";//+str;
		//return err.c_str();
		return "Value error";
	}

	/*virtual string what(string str) const throw()
	{
		return "Value error: in " + str;
	}*/

};

bool is_number(const string& s)
{
	string::const_iterator it = s.begin();
	while(it != s.end() && std::isdigit(*it) ) ++it;
	return !s.empty() && it == s.end();
}

inline int stringToInt(string s) //throw(const char *)
{
	stringstream o(s);
	int x;
	o>>x;
	if(x == 0)
	{
		if(!is_number(s))
		{
			throw ValueErrorException();
		}
	}
	return x;
}

void myterminate()
{
	std::cerr << "Terminate Called\n";

}

int main2()
{
	std::set_terminate(myterminate);
	//int x;
	try
	{
		int x = stringToInt("a1232");
		cout<<x<<endl;

	}catch(const char* s)
	{
		cout<<"Zero!"<<endl;
	}
	catch(ValueErrorException& e)
	{
		cout<<e.what()<<endl;
	}
	catch(...)
	{
		cout<<"NO!"<<endl;
	}
		
	return 0;
}

void sigAbort( int signum)
{
	cout<<"Interrupt"<<endl;
	exit(signum);
}

int main()
{
	signal(SIGABRT, sigAbort);
	main2();
//	throw 4;
	return 0;
}
