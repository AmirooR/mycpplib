#include "net/CURLHTTPManager.h"

int main()
{
	HTTPManager* http_manager = new CURLHTTPManager();
	struct MemoryStruct chunk = http_manager->sendQuery("http://localhost/~amirrahimi/");
	for(int i = 0; i < chunk.size; ++i)
	{
		cout<<chunk.memory[i];
	}
	cout<<endl;
	delete http_manager;
	return 0;
}
