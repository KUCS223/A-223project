all:
	gcc -c cat.c
	gcc -c ls.c
	gcc -c help.c
	gcc -c exit.c
	gcc -c Server.c
	gcc -c WCfun.c
	gcc -c rewt.c
	gcc -c Clinet.c	
	gcc -c retrieves.c
	gcc -c stats.c
	gcc -c Networks.c
	gcc help.o Networks.o retrieves.o stats.o rewt.c WCfun.o exit.o ls.o cat.o Server.o -o program
	gcc rewt.o Networks.o Clinet.o -o clinet 
	
	


createObj:
	gcc -c cat.c 
	gcc -c ls.c
	gcc -c help.c
	gcc -c exit.c
	gcc -c Server.c
	gcc -c WCfun.c
	gcc -c rewt.c
	gcc -c Clinet.c
	gcc -c retrieves.c
	gcc -c stats.c
	gcc -c Networks.c
createSlinkDynSer:
	 
	 gcc help.o Networks.o retrieves.o stats.o rewt.c WCfun.o exit.o ls.o cat.o Server.o -o program
	
createSlinkDynCli:
	
	gcc rewt.o Networks.o Clinet.o -o clinet
clean:
	rm ls.o 
	rm exit.o 
	rm rewt.o 
	rm stats.o  
	rm WCfun.o 
	rm retrieves.o	
	rm cat.o 
	rm help.o 
	rm Networks.o 
	rm Server.o 
	rm Clinet.o
	rm clinet 
	rm program
	
