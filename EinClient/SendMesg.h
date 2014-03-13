#include "../Include/Network.h"
#include <iostream>
#include <string>
using std::string;

string SendMesg(string& send_mesg);
ssize_t writen(int fd, const void* vptr, size_t n);
ssize_t my_read(int fd, char* ptr);
ssize_t readline(int fd, void* vptr, size_t maxlen);

