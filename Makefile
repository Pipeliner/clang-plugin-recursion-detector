all: c
c: clanglib.c
	clang clanglib.c -I/usr/lib/llvm-3.5/include -L /usr/lib/llvm-3.5/lib/ -lclang -o c
