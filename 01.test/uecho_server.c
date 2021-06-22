#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define BUFSIZE 1024

void err_handle(char *msg);
int main(int argc, char *argv[])
{
    int ser_socket;
    struct sockaddr_in ser_addr, cln_addr;
    int cln_addr_sz, recv_cnt;
    char buf[BUFSIZE];

    if (argc != 2)
    {
        fprintf(stdout, "Usage:%s <port>\r\n", argv[0]);
        exit(1);
    }
    fprintf(stdout, "hello xptd for udp_echo_server\r\n");

    ser_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (ser_socket == -1)
    {
        err_handle("socket() err\r\n");
    }

    memset(&ser_addr, 0, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    ser_addr.sin_port = htons(atoi(argv[1]));
    if (bind(ser_socket, (struct sockaddr *)&ser_addr, sizeof(ser_addr)) == -1)
    {
        err_handle("bind() err\r\n");
    }
    while (1)
    {
        cln_addr_sz = sizeof(cln_addr);
        recv_cnt = recvfrom(ser_socket, buf, BUFSIZE, 0, (struct sockaddr *)&cln_addr, &cln_addr_sz);
        sendto(ser_socket, buf, recv_cnt, 0, (struct sockaddr *)&cln_addr, sizeof(cln_addr));
    }

    close(ser_socket);
    return 0;
}

void err_handle(char *msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}