words_count: words_count.o lexer.o -lfl
	gcc words_count.o lexer.o -lfl -o words_count

words_count.o: words_count.c
	gcc -c words_count.c

lexer.o: lexer.c
	gcc -c lexer.c

lexer.c: lexer.l
	flex -t lexer.l > lexer.c
