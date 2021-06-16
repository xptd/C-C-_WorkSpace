#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

void error_hanlde(char * msg);

int main(int argc, char * argv[]){
    int server_socket =-1;
    int client_socket =-1;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int client_addr_size=0;    
    char message[]="hello xptd for server test\r\n";

    fprintf(stdout,"hello xptd for server!\r\n");
    if (argc != 2){
        fprintf(stdout,"Usage:%s <port>\r\n",argv[0]);
        exit(1);
    }
    server_socket = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
    if( server_socket == -1){
        error_hanlde("socket() err");
    }
    memset(&server_addr,0,sizeof(server_addr));
    memset(&client_addr,0,sizeof(client_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    server_addr.sin_port=htons(atoi(argv[1]));

   if(bind(server_socket,(struct sockaddr *)&server_addr,sizeof(server_addr)) == -1){
       error_hanlde("bind() err");
   }

    if ( listen(server_socket,5) == -1){
        error_hanlde("listen() err");
    }

    client_addr_size=sizeof(client_addr);
    client_socket=accept(server_socket,(struct sockaddr *)&client_addr,&client_addr_size);
    if (client_socket == -1){
       error_hanlde("accept() err"); 
    }
   if( (write(client_socket,message,sizeof(message))) == -1){
       error_hanlde("write() error");
   }
   close(client_socket);
   close(server_socket);
    return 0;
}
void error_hanlde(char * msg){
    fprintf(stderr,"%s\r\n",msg);
    exit(1);
}