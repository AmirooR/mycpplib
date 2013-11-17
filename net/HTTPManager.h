#ifndef _HTTP_MANAGER_H_
#define _HTTP_MANAGER_H_

#include "util/utils.h"

class HTTPManager
{
	protected:
		string user;
		string pass;
		bool use_pass;
	public:
		HTTPManager():use_pass(false){}

		HTTPManager(bool use_pass, string user, string pass) : use_pass(use_pass), user(user), pass(pass){}

//		virtual ~HTTPManager(){}

		virtual struct MemoryStruct sendQuery(string url) = 0;

		void setUser(string user){ this->user = user; }
		void setPass(string pass){ this->pass = pass; }
		void setUsePass(bool use_pass){ this->use_pass = use_pass; }

		string getPass(){return pass;}
		string getUser(){return user;}
		bool getUsePass(){return use_pass;}
		virtual ~HTTPManager(){}
};

#endif
