all: c
c: clanglib.cpp callgraph.cpp
	clang++ clanglib.cpp callgraph.cpp -I/usr/lib/llvm-3.5/include -L /usr/lib/llvm-3.5/lib/ -lclang -o c
