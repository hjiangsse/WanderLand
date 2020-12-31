words_count: words_count.o lexer.o -lfl
	gcc $^ -o $@

words_count.o: words_count.c
	gcc -c $<

lexer.o: lexer.c
	gcc -c $<

lexer.c: lexer.l
	flex -t $< > $@
