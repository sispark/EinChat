#include "../Include/Network.h"
#include <iostream>

using std::cout;
using std::endl;

//将消息写入socket
ssize_t writen(int fd, const void* vptr, size_t n) {
    size_t nleft;
    ssize_t nwritten;
    const char* ptr;

    ptr = (const char*)vptr;
    nleft = n;
    while(nleft > 0) {
        nwritten = write(fd, ptr, nleft);
        nleft -= nwritten;
        ptr += nwritten;
    }
    return n;
}

void str_echo(int sockfd) {
    ssize_t n;
    char buf[MAXLINE];

    while((n = read(sockfd, buf, MAXLINE)) > 0) {
        cout<<"Receive Mesg on Sever:"<<buf<<endl;
        writen(sockfd, buf, n);
    }
}

int main(int argc, char** argv) {
    int listenfd, connfd;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    
    bind(listenfd, (SA*)&servaddr, sizeof(servaddr));
    listen(listenfd, LISTENQ);

    for(;;) {
        clilen = sizeof(cliaddr);
        connfd = accept(listenfd, (SA*)&cliaddr, &clilen);
        if((childpid = fork()) == 0) {
            close(listenfd);
            str_echo(connfd);
            exit(0);
        }
        close(connfd);
    }

    return 0;
}

