#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <string.h>
#define BACKLOG 10

void error(char *s){
  printf("Error: %s\n",s);
  exit(1);
}

int main(int argc, char *argv[]){
  // create socket
  int fd=socket(AF_INET,SOCK_STREAM,0);
  if(fd<0) perror("ERROR: can not create socket\n");
  // TODO set options
  // bind to socket
  struct sockaddr_in addr;
  addr.sin_family=AF_INET;
  addr.sin_port= htons(1122);
  addr.sin_addr.s_addr=inet_addr("10.10.0.1");
  socklen_t len=sizeof(addr);
  int b=bind(fd,(struct sockaddr *)&addr,len);
  printf("%i\n",b);
  if(b<0) error("Error on binding\n");
  // listen to client
  int l= listen(fd,BACKLOG);
  if(l<0) error("Error on listen\n");
  // accept connection
  int addr_len=sizeof(addr);
  int new_socket= accept(fd,(struct sockaddr *)&addr,(socklen_t*)&addr_len);
  if(new_socket<0) error("Error on accepting connection\n");
  char buf[100];
  unsigned short chat=1;
  while(chat){

    if(strcmp(buf,"exit")!=0 && chat!=0){
      read(new_socket,&buf,256);
      printf("Message is: %s\n",buf);
    }else{
      chat=0;
    }
  }
  close(fd);
  return 0;
}