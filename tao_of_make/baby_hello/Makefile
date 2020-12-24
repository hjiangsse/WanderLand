hello: hello.o foo.o
	clang hello.o foo.o -o hello

foo.o: foo.c foo.h
	clang -c foo.c

hello.o: hello.c
	clang -c hello.c
