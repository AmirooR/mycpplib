#ifndef _CONFIG_MGR_
#define _CONFIG_MGR_

#include <string>
#include <map>
#include <set>
#include "rapidxml/rapidxml_utils.hpp"

using namespace std;

class ConfigurationManager
{
	protected:
	rapidxml::xml_document<> doc;
	map<string, string> keyValMap;
	public:
	void readConfigFile(const char* filename, const char* first_node_name = NULL)
	{
		rapidxml::file<> xmlFile(filename);
		doc.parse<0>(xmlFile.data());
		for( rapidxml::xml_node<>* key_node = doc.first_node(first_node_name)->first_node(); key_node; key_node = key_node -> sibling() )
		{
			keyValMap[key_node->name] = key_node->value()
		}
	}

	inline string getVal( string key)
	{
		return keyValMap[key];
	}

	inline void setKeyVal( string key, string val )
	{
		keyValMap[key] = val;
	}

	inline bool hasKey( string key )
	{
		return keyValMap[key].length() != 0;
	}

};


#endif
