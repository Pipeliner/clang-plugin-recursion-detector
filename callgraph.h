#include <clang-c/Index.h>
#include <clang-c/Platform.h>
#include <stdio.h>
#include <string>

typedef std::string string;

const int MAX_NODES = 100;

class Graph
{
public:
	int nodesCount;
	string nodes[MAX_NODES];
	int edges[MAX_NODES][MAX_NODES];
	void addNode(string node);
	void addEdge(string src, string dst);
private:
	int indexOfNode(string node);
};

class CallGraph
{
public:
	CallGraph (int argc, const char * argv[]);
	Graph *directGraph;
	Graph *transitiveClosureGraph();
private:
	Graph mTransitiveClosureGraph;
	//enum CXChildVisitResult cursorVisitor(CXCursor cursor, CXCursor parent, CXClientData client_data);
};