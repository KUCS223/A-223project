all:
	gcc -c cat.c
	gcc -c ls.c
	gcc -c help.c
	gcc -c exit.c
	gcc -c main.c
	gcc -c WCfun.c 
	ar rcs -o lib.a WCfun.o cat.o help.o exit.o ls.o
	gcc -static -o program main.o lib.a

createObj:
	gcc -c cat.c 
	gcc -c ls.c
	gcc -c help.c
	gcc -c exit.c
	gcc -c WCfun.c
	gcc -c main.c	

createLib:
	ar rcs -o lib.a cat.o WCfun.o help.o exit.o ls.o

linkSt:
	gcc -static -o program main.o lib.a
clean:
	rm main.o
	rm cat.o 
	rm lib.a
	rm ls.o
	rm help.o
	rm exit.o
	rm WCfun.o
	rm program 
