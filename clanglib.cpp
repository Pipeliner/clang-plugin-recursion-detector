#include <iostream>
#include "callgraph.h"

int usage(const std::string executableName) {
	std::cout << "Usage: " << executableName << " source-file.c [source-file-2.c ...]" << std::endl;
	return 1;
}

void processSourceFile(std::string fileName) {
	CallGraph graph(fileName);
	std::cout << "Processing file " << fileName << std::endl;
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

int main (int argc, const char * argv[]) {
	if (argc < 2)
		return usage(argv[0]);

	for (int i = 1; i < argc; i++)
		processSourceFile(argv[i]);

	return 0;
}


