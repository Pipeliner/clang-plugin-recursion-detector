#include "callgraph.h"
const char *caller;

enum CXChildVisitResult cursorVisitor(CXCursor cursor, CXCursor parent, CXClientData client_data);

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

int Graph::indexOfNode(string node)
{
	for (int i = 0; i < nodesCount; i++)
		if (nodes[i] == node)
			return i;

	throw "No such node: " + node;
}



CallGraph::CallGraph(int argc, const char * argv[])
{
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
        //printf("method '%s'\n",clang_getCString(name));        
        CXSourceLocation location = clang_getCursorLocation(cursor);   
        
        CXString filename;
        unsigned int line, column;
        
        clang_getPresumedLocation(location, &filename, &line, &column);
        
        //printf("%s : %s, (%i,%i)\n",clang_getCString(name),clang_getCString(filename),line,column);
        caller = clang_getCString(name);
        return CXChildVisit_Recurse;
    }
    else if (kind == CXCursor_CallExpr)
    {
    	printf("call %s -> %s\n", caller, clang_getCString(name));
    	return CXChildVisit_Recurse;
    }
    return CXChildVisit_Recurse;
}