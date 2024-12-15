#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <signal.h>
#include <sys/stat.h>

#define MAXLINE 1024
#define LISTENQ 5

int open_listenfd(char *port){
    struct addrinfo hints, *listp, *p;
    int listenfd, rc, optval=1;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;
    hints.ai_flags |= AI_NUMERICSERV;
    if((rc = getaddrinfo(NULL,port,&hints,&listp))!=0){
        exit(1);
    }

    for(p=listp; p; p=p->ai_next){
        if((listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
            continue;
        setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,
                   (const void *)&optval ,sizeof(int));
        if (bind(listenfd,p->ai_addr,p->ai_addrlen)==0)
            break;
        if (close(listenfd)<0) {
            exit(1);
        }
    }
    freeaddrinfo(listp);
    if (!p) {
        exit(1);
          }
    if (listen(listenfd,LISTENQ)<0) {
        close(listenfd);
              exit(1);
    }
    return listenfd;
}
int open_clientfd(char *hostname, char *port) {
    int clientfd, rc;
    struct addrinfo hints, *listp, *p;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_NUMERICSERV;
    hints.ai_flags |= AI_ADDRCONFIG;
    if ((rc=getaddrinfo(hostname,port,&hints,&listp))!=0){
        exit(1);
    }
    for (p=listp; p; p=p->ai_next) {
        if ((clientfd = socket(p->ai_family,p->ai_socktype,p->ai_protocol)) < 0)
            continue;

        if(connect(clientfd,p->ai_addr,p->ai_addrlen)!=-1)
            break;
        if(close(clientfd)<0) {
            exit(1);
        }
    }
    freeaddrinfo(listp);
    if(!p){
        exit(1);
    }else{
        return clientfd;
    }   
}
