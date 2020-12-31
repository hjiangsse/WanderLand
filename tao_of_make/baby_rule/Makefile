.PHONY: all
all: shownewer size check-space main

main: main.o sing.o small_sing.o
	echo $@
	gcc main.o *sing.o -o main
main.o: main.c
	gcc -c main.c
sing.o: sing.c sing.h
	gcc -c sing.c
small_sing.o: small_sing.c sing.h
	gcc -c small_sing.c

.PHONY: check-space
check-space:
	@df -h . | awk 'NR == 2 { printf( "%dGB available\n", $$4) }'

.PHONY: showmsg
showmsg:
	@echo "This is the beginning of a new world!"
	@echo "Welcome to the world of GNU make!"

.PHONY: shownewer
shownewer: *.[hc]
	lpr $?

size: main.c
	size main 
	touch size

