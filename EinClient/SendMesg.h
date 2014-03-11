#include "../Include/Network.h"
#include <iostream>

void SendMesg(const char* send_mesg);
ssize_t writen(int fd, const void* vptr, size_t n);
ssize_t my_read(int fd, char* ptr);
ssize_t readline(int fd, void* vptr, size_t maxlen);

