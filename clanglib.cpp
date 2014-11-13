#include <iostream>
#include "callgraph.h"

int main (int argc, const char * argv[])
{
	CallGraph graph(argc, argv);
	std::cout << "Call graph adjacency matrix:" << std::endl;
	graph.directGraph->printMatrix();
	std::cout << std::endl;

	std::cout << "Call graph transitive closure adjacency matrix:" << std::endl;
	graph.transitiveClosureGraph()->printMatrix();
	int n = graph.directGraph->nodesCount;
	std::cout << "Recursive functions: ";
	for (int i = 0; i < n; i++)
		if (graph.transitiveClosureGraph()->edges[i][i])
			std::cout << graph.directGraph->nodes[i] << ", ";
	std::cout << std::endl;
}


