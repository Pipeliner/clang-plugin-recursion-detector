#include <iostream>
#include "callgraph.h"

int main (int argc, const char * argv[])
{
	CallGraph graph(argc, argv);
	graph.directGraph->printMatrix();
}


