
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

#define BUFLEN 512
void err_handle(char * msg){
    fputs(msg,stderr);
    fputc('\n',stderr);
    exit(1);
}

int main(int argc, char* argv[]){

    int client_socket = -1;
    struct sockaddr_in server_addr;
    int read_len = 0;
    char buf[BUFLEN];
    int str_len =-1;
    fprintf(stdout,"hello xptd for client\r\n");
    if (argc != 3){
        fprintf(stdout,"Usage:%s <ip> <port>\r\n",argv[0]);
        exit(1);
    }
    client_socket = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(client_socket == -1){
        err_handle("socket() error");
    }
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=inet_addr(argv[1]);
    server_addr.sin_port=htons(atoi(argv[2]));

   if ( connect(client_socket,(struct sockaddr *)&server_addr,sizeof(server_addr)) == -1){
       err_handle("connect() error");
   }
   str_len= read(client_socket,buf,BUFLEN-1);
    if (str_len == -1){
        err_handle("read()");
    }
    fprintf(stdout,"read from server:%s\r\n",buf);
    return 0;

}