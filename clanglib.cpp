//#include <iostream>


#include "callgraph.h"


void printTokenInfo(CXTranslationUnit translationUnit,CXToken currentToken);
void printCursorTokens(CXTranslationUnit translationUnit,CXCursor currentCursor);

enum CXChildVisitResult cursorVisitor(CXCursor cursor, CXCursor parent, CXClientData client_data);
enum CXChildVisitResult functionDeclVisitor(CXCursor cursor, CXCursor parent, CXClientData client_data);







int main (int argc, const char * argv[])
{
	CallGraph graph(argc, argv);
}


