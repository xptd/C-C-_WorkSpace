
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/socket.h>
// #include <arpa/inet.h>

// int main(){
//     union{
//         int a;
//         char b;
//     }test;


//     test.a=0x1;
//     unsigned short port=0x1234;
//     unsigned long ip=0x12345678;
//     fprintf(stdout, "%d\r\n",test.b);
//     fprintf(stdout,"port:%p\r\n",&port);

//     fprintf(stdout,"ip:%p\r\n",&ip);
//     fprintf(stdout, "%x\r\n",htons(0x1234));
//     fprintf(stdout, "%x\r\n",htonl(0x12345678));
//     return 0;

// }


// #include <stdio.h>
// #include <stdlib.h>
// #include <arpa/inet.h>

// int main(){
//     //C0A80201
//     char *addr1="192.168.2.1";
//     char *addr2="172.16.11.123";
//     unsigned long caddr1=inet_addr(addr1);
//     unsigned long caddr2 = inet_addr(addr2);
//     if (caddr1 == INADDR_NONE){
//         fprintf(stdout,"addr1 convert err\r\n");
//         exit(1);
//     }
//     fprintf(stdout,"%#lx\r\n",caddr1);
//     if(caddr2 == INADDR_NONE){
//         fprintf(stdout,"addr2 convert err\r\n");
//         exit(1);
//     }
//     fprintf(stdout,"%#lx\r\n",caddr2);
//     return 0;

// }


#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#include <arpa/inet.h>

//inet_addr
//inet_aton
//inet_ntoa

int main(int argc, char *argv[]){
    unsigned int conv_addr;
    struct sockaddr_in saddr;
    if(argc != 2){
        fprintf(stdout,"Usage:%s <ip>\r\n",argv[0]);
        exit(1);
    }
    fprintf(stdout, "input ip:%s\r\n",argv[1]);
 
    conv_addr = inet_addr(argv[1]);

    if (conv_addr == INADDR_NONE){
        fprintf(stdout,"inet_addr() addr convert err\r\n");
        exit(0);
    }
    fprintf(stdout,"%#x\r\n",conv_addr);
    if( !(inet_aton(argv[1], &(saddr.sin_addr))) ){
        fprintf(stdout,"inet_aton() convert addr err\r\n");
        exit(0);
    }
    fprintf(stdout,"%#x\r\n",saddr.sin_addr.s_addr);
    
    fprintf(stdout,"reconvert str:%s\r\n",inet_ntoa(saddr.sin_addr));

    return 0;
}