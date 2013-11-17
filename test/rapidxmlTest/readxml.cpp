#include <iostream>
//#include <fstream>
//#include <vector>

#include "rapidxml/rapidxml_utils.hpp"

int main()
{
	rapidxml::file<> xmlFile("test.xml");
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());
	char* name = NULL;
	std::cout<<" Name of first node is: "<<doc.first_node(name)->name() << std::endl;
	for( rapidxml::xml_node<>* _node = doc.first_node()->first_node();_node; _node = _node->next_sibling() )
	{
		std::cout<< "\tNode name: " << _node->name() << std::endl;
	}
	return 0;
}
