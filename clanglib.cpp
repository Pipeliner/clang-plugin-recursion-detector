#include <iostream>
#include "callgraph.h"

int main (int argc, const char * argv[])
{
	CallGraph graph(argc, argv);
	int functionsCount = graph.directGraph->nodesCount;
	std::cout << "  ";
	for (int dst = 0; dst < functionsCount; dst++)
		std::cout << graph.directGraph->nodes[dst];
	std::cout << std::endl;
	for (int src = 0; src < functionsCount; src++)
	{
		std::cout << graph.directGraph->nodes[src] << " ";
		for (int dst = 0; dst < functionsCount; dst++)
			std::cout << graph.directGraph->edges[src][dst];

		std::cout << std::endl;
	}
}


