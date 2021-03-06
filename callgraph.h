#include <clang-c/Index.h>
#include <clang-c/Platform.h>
#include <stdio.h>
#include <string>

typedef std::string string;

const int MAX_NODES = 100;

class Graph
{
public:
	Graph();
	int nodesCount;
	string nodes[MAX_NODES];
	int edges[MAX_NODES][MAX_NODES];
	void addNode(string node);
	void addEdge(string src, string dst);
	void printMatrix();
private:
	int indexOfNode(string node);
};

class CallGraph
{
public:
	CallGraph (const std::string fileName);
	static Graph *directGraph;
	Graph *transitiveClosureGraph();
	static string currentCaller; // Global state here due to problems with c->c++ member callbacks

private:
	Graph *mTransitiveClosureGraph;
};