all: c
c: clanglib.cpp callgraph.cpp
	clang++ -g clanglib.cpp callgraph.cpp -I/usr/lib/llvm-3.8/include -L /usr/lib/llvm-3.8/lib/ -lclang -o c
