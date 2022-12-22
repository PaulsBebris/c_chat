#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void error(char *s){
  printf("Error: %s\n",s);
  exit(1);
}

int main(int argc, char *argv[]){
  int fd= socket(AF_INET,SOCK_STREAM,0);
  if(fd<0) error("Error creating socket\n");
  struct sockaddr_in addr;
  addr.sin_family=AF_INET;
  inet_pton(AF_INET,"10.10.0.1",&addr.sin_addr);
//  addr.sin_addr.s_addr= inet_addr("10.10.0.1");
  addr.sin_port= htons(1122);
  int c=connect(fd,(struct sockaddr *)&addr, (socklen_t)sizeof(addr));
  if(c<0) error("Error on connection\n");
  unsigned short chat=1;
  while(chat) {
    char msg[100] = {0};
    puts("Enter your message\n");
    fgets(msg, 100, stdin);
    if (strcmp(msg, "exit") != 0) {
      send(fd, msg, strlen(msg), 0);
    } else {
      send(fd, msg, strlen(msg), 0);
      chat = 0;
    }
  }
  close(fd);
  return 0;
}