#include <iostream>
#include "callgraph.h"

enum CXChildVisitResult cursorVisitor(CXCursor cursor, CXCursor parent, CXClientData client_data);

Graph::Graph()
{
    //for (int i = 0; i < MAX_NODES; i++)
    //    nodes[i] = 0;
    for (int src = 0; src < MAX_NODES; src++)
        for (int dst = 0; dst < MAX_NODES; dst++)
            edges[src][dst] = 0;
\
}

void Graph::addNode(string node)
{
	for (int i = 0; i < nodesCount; i++)
		if (nodes[i] == node)
			return;

	//new node
	if (nodesCount == MAX_NODES)
		throw "Too many edges";

	nodes[nodesCount++] = node;
}

void Graph::addEdge(string src, string dst)
{
	edges[indexOfNode(src)][indexOfNode(dst)] = 1;
}

void Graph::printMatrix()
{
    std::cout << "  ";
    for (int dst = 0; dst < nodesCount; dst++)
        std::cout << nodes[dst];
    std::cout << std::endl;
    for (int src = 0; src < nodesCount; src++)
    {
        std::cout << nodes[src] << " ";
        for (int dst = 0; dst < nodesCount; dst++)
            std::cout << edges[src][dst];

        std::cout << std::endl;
    }
}

int Graph::indexOfNode(string node)
{
	for (int i = 0; i < nodesCount; i++)
		if (nodes[i] == node)
			return i;

	throw "No such node: " + node;
}

string CallGraph::currentCaller; //http://stackoverflow.com/questions/272900/vectorpush-back-odr-uses-the-value-causing-undefined-reference-to-static-clas
Graph *CallGraph::directGraph;

CallGraph::CallGraph(int argc, const char * argv[])
{
    directGraph = new Graph();
	CXIndex index = clang_createIndex(0, 0);
    
    if(index == 0)
        throw "Error creating index";


    CXTranslationUnit translationUnit = clang_parseTranslationUnit(index, 0,
                                                      argv, argc, 0, 0, CXTranslationUnit_None);
    
    if(translationUnit == 0)
        throw "Error creating translationUnit\n";
    
    CXCursor rootCursor = clang_getTranslationUnitCursor(translationUnit);

    unsigned int res = clang_visitChildren(rootCursor, *cursorVisitor, 0);
    
    clang_disposeTranslationUnit(translationUnit);
    clang_disposeIndex(index);

}
enum CXChildVisitResult cursorVisitor(CXCursor cursor, CXCursor parent, CXClientData client_data){
    
    enum CXCursorKind kind = clang_getCursorKind(cursor);
    CXString name = clang_getCursorSpelling(cursor);
    if (kind == CXCursor_FunctionDecl || kind == CXCursor_ObjCInstanceMethodDecl)
    {
        CallGraph::currentCaller = clang_getCString(name);
        CallGraph::directGraph->addNode(CallGraph::currentCaller);
        return CXChildVisit_Recurse;
    }
    else if (kind == CXCursor_CallExpr)
    {
    	printf("call %s -> %s\n", CallGraph::currentCaller.c_str(), clang_getCString(name));
        CallGraph::directGraph->addEdge(CallGraph::currentCaller, clang_getCString(name));
    	return CXChildVisit_Recurse;
    }
    clang_disposeString(name);
    return CXChildVisit_Recurse;
}