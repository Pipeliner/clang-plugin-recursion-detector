//#include <iostream>
#include <clang-c/Index.h>
#include <clang-c/Platform.h>
#include <stdio.h>



void printTokenInfo(CXTranslationUnit translationUnit,CXToken currentToken);
void printCursorTokens(CXTranslationUnit translationUnit,CXCursor currentCursor);

enum CXChildVisitResult cursorVisitor(CXCursor cursor, CXCursor parent, CXClientData client_data);
enum CXChildVisitResult functionDeclVisitor(CXCursor cursor, CXCursor parent, CXClientData client_data);

const char *caller;

int main (int argc, const char * argv[])
{
    CXIndex index = clang_createIndex(0, 0);
    
    if(index == 0){
        fprintf(stderr, "error creating index\n");
        return 1;
    }

    CXTranslationUnit translationUnit = clang_parseTranslationUnit(index, 0,
                                                      argv, argc, 0, 0, CXTranslationUnit_None);
    
    if(translationUnit == 0){
        fprintf(stderr, "error creating translationUnit\n");
        return 1;
    }
    

    
    CXCursor rootCursor = clang_getTranslationUnitCursor(translationUnit);
    
    //printCursorTokens(translationUnit,rootCursor);
    
    unsigned int res = clang_visitChildren(rootCursor, *cursorVisitor,0);
    
    clang_disposeTranslationUnit(translationUnit);
    clang_disposeIndex(index);
    return 0;
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
