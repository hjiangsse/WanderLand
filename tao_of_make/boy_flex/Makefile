CPPFLAGS = -I include
vpath %.c src
vpath %.l src
vpath %.h include

CC = clang
RM = rm

words_count: counter.o lexer.o -lfl
words_count.o: counter.h
counter.o: counter.h lexer.h
lexer.o: lexer.h

%: %.o
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $(CPPFLAGS) -c $<

lexer.c: lexer.l
	@$(RM) $@
	flex -t $< > $@

clean:
	@$(RM) *.o words_count 
