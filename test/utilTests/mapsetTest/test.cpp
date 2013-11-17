#include <map>
#include <set>
#include <string>
#include <vector>
#include <iostream>

using namespace std;


int main()
{
	map<string, string> keyVals;
	keyVals["amir"] = "khoob";
	keyVals["hasan"] = "bad";
	cout<< keyVals["amir"] << endl;

	cout<< keyVals["hasan"] << endl;

	cout<< keyVals["gholi"].length() << endl;
	return 0;
}
