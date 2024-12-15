# The Name of Project is AB-223Project

# Created by  ALi ALKHULAIFI -> 2212172438



                                                               
--> Project <Part (3)>


> To Compile Project using Makefile

* make createObj --------------> Create Object files

* make createLib -------------> Using object files to create static libary with name lib.a

* make createDyn --------------> This do dynamic linking for Networking and function that use for send and resevied between 
server or clinet

* make linkSt   --------------> Static linking: Static libary with main program

* make LinkDy ------------- > That linking dynamic 

* ./program     -------------> Run program

> Optional in Makefile

* make then ./program ---------------> Easy way to run project, will do createObj/createLib/linkSt

* make clean ------> delete all object file , exeutable file and static libary file which is lib.a


> List all project file
* Server.c: That resevied shell command from clinet and run command then send data with encryption to clinet
* Clinet.c: C file that resived data from server using Network and run it in print it in screen of clinet 
* cat.c:  C file that include the code of cat command that print content of file
* ls.c:   C file that include the code of ls command that list a directry
* help.c: File that print all command and what should they do
* exit.c: File that exit the program using signal
* WCfun.c: C file that include all function that use it for wildcard
* sample:  Directory that use it for test the project

* NetworkCli.c: C file that have Network code for Server and Clinet 
* stats.c: C file that count of send it byte, clinet accept connection,how many file Download and send the byte of downloaded file
* retrieves.c: C file that send files from server that clinet would to download it also send flag the tell clinet is download it file
* rewt.c: C file that do short write and short write and use it clinet and server also decrypt data from server  
* Makefile: That complie the code using a simples commands 
* password.txt: A Large text file 
* big.txt: A Large text file

--> For Part3 there is encrypt before send data to clinet then the clinet decrypt the data

                               ----------------------------------------


* Project created by -> Ali Alkhulaifi  


