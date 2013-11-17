#ifndef _CURLHTTP_MANAGER_
#define _CURLHTTP_MANAGER_

#include "HTTPManager.h"
#include <curl/curl.h>
#include <curl/easy.h>


class CURLHTTPManager: public HTTPManager
{
	//static int num_handles;
protected:
	CURL* curl_handle;
	CURLcode curlRes;
//	bool started;

public:
	CURLHTTPManager():HTTPManager()
	{
		curl_global_init(CURL_GLOBAL_ALL);
		curl_handle = 0;
	}

	CURLHTTPManager( bool use_pass, string user, string pass):HTTPManager(use_pass, user, pass)
	{
		curl_global_init(CURL_GLOBAL_ALL);
		curl_handle = 0;
	}

	struct MemoryStruct sendQuery(string url)
	{
		struct MemoryStruct chunk;

		chunk.memory=NULL; /* we expect realloc(NULL, size) to work */
		chunk.size = 0;
		if(curl_handle)
			curl_easy_cleanup(curl_handle);
		curl_handle = curl_easy_init();

		curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
		curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);

		curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

		if(use_pass)
		{
			std::string sAuth("");
			sAuth += user + ":" + pass;
			curl_easy_setopt(curl_handle, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
			curl_easy_setopt(curl_handle, CURLOPT_USERPWD, sAuth.c_str());
		}

		curlRes = curl_easy_perform(curl_handle);
		if(CURLE_OK != curlRes) 
		{
			std::cerr<<"Url: "<<url<<" not reachable!"<<std::endl;
			if(chunk.memory)
			{
				free(chunk.memory);
			}
			chunk.size = 0;
		}
		return chunk;
	}

	~CURLHTTPManager()
	{
		cerr<<"Releasing CURL"<<endl;
		curl_easy_cleanup( curl_handle);
		curl_global_cleanup();
	}

};

#endif
