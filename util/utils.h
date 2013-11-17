#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <exception>
#include <time.h>
#include <unistd.h> //TODO: fix for windows
#include <iomanip>
#include <sstream>

using namespace std;

struct MemoryStruct {
  char *memory;
  size_t size;
};

class ATime 
{
	//TODO: fix for windows
	int year, month, day;
public:
	ATime(int year, int month, int day):year(year),month(month),day(day)
	{
	}

	ATime()
	{
		setToNow();
	}

	void setToNow()
	{
		time_t m_t = time(0);
		struct tm* t = localtime(&m_t);
		year = t->tm_year + 1900;
		month = t->tm_mon + 1;
		day = t->tm_mday;
	}

	int getYear(){return year;}
	int getMonth(){return month;}
	int getDay(){return day;}

	void setYear(int year){this->year = year;}
	void setMonth(int month){this->month = month;}
	void setDay(int day){this->day = day;}

	string toString()
	{
		stringstream o;
		o<<year<<"/"<<month<<"/"<<day;
		return o.str();
	}

};

static void *myrealloc(void *ptr, size_t size)
{
  /* There might be a realloc() out there that doesn't like reallocing
     NULL pointers, so we take care of it here */
  if(ptr)
    return realloc(ptr, size);
  else
    return malloc(size);
}

int lcs(std::string& a,std::string& b)
{
    int n = a.length();
    int m = b.length();
    //allocating s
    int **s;
    s = new int*[n+1];
    int i,j;
    for(i=0;i<n+1;i++)
    {
        s[i] = new int[m+1];
        for(j=0;j<m+1;j++)
        {
            s[i][j] = 0;
        }
    }

    for(i=1;i<=n;++i)
    {
        for(j=1;j<=m;++j)
        {
            if(a[i-1] == b[j-1])
            {
                int val = s[i-1][j-1];
                s[i][j] = val+1;
            }
            else
            {
                s[i][j] = s[i-1][j-1];
            }

            if(s[i-1][j] >= s[i][j])
            {
                s[i][j] = s[i-1][j];
            }

            if(s[i][j-1] >= s[i][j])
            {
                s[i][j] = s[i][j-1];
            }
        }
    }

    int ret = s[n][m];
    for(i=0;i<n+1;i++)
    {
        delete[] s[i];
    }
    delete[] s;
    return ret;
}


static size_t
WriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)data;

  mem->memory = (char *)myrealloc(mem->memory, mem->size + realsize + 1);
  if (mem->memory) {
    memcpy(&(mem->memory[mem->size]), ptr, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
  }
  return realsize;
}

std::string tempName()
{
	//std::string ret = "";
	char s[33] = {0};
	//dlib::rand r;
	for(int i=0;i<32;i++)
	{
		char c = (rand() % 26) + 'A';
		s[i] = c;
	}
	s[32] = 0;
	std::string ret(s);
	return ret;
}

void writeMemToFile(struct MemoryStruct data,const char* fileName)
{

	FILE* f = fopen(fileName,"wb");
	for(unsigned int i=0;i<data.size;i++) //TODO: check size-1 or size
	{
		fprintf(f,"%c",data.memory[i]);
	}
	fprintf(f, "%c", '\0');
	fclose(f);
}



bool haveNoIntersection(std::vector<std::string> &a,std::vector<std::string> &b, int minSize = 5)
{
	for(int i=0;i<a.size();i++)
	{
		bool haveSimilar = false;
		for(int j=0;j<b.size();j++)
		{
			if( lcs(a[i],b[j]) > minSize || a[i].compare(b[j])==0)
			{
				haveSimilar = true;
				break;
			}
		}

		if(!haveSimilar)
		{
			return true;
		}
	}
	return false;
}



#endif
