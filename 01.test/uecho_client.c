#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUF_SIZE 1024

void err_handle(char *);
int main(int argc, char *argv[])
{
    int cln_socket = -1;
    struct sockaddr_in ser_addr;
    char buf[BUF_SIZE];
    int recv_cnt = 0;
    int adr_sz = 0;
    if (argc != 3)
    {
        fprintf(stdout, "Usage:%s <ip> <port>\r\n", argv[0]);
        exit(1);
    }
    fprintf(stdout, "hello xptd for udp_echo_client\r\n");

    cln_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (cln_socket == -1)
    {
        err_handle("socket() err\r\n");
    }
    memset(&ser_addr, 0, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = inet_addr(argv[1]);
    ser_addr.sin_port = htons(atoi(argv[2]));
    adr_sz = sizeof(ser_addr);
    while (1)
    {
        fputs("Please input a string(q\\Q quit):", stdout);
        fgets(buf, BUF_SIZE, stdin);
        if (!strcmp(buf, "q\n") || !strcmp(buf, "Q\n"))
        {
            break;
        }
        sendto(cln_socket, buf, strlen(buf), 0, (struct sockaddr *)&ser_addr, sizeof(ser_addr));
        recv_cnt = recvfrom(cln_socket, buf, BUF_SIZE - 1, 0, (struct sockaddr *)&ser_addr, &adr_sz);
        buf[recv_cnt] = 0;
        fprintf(stdout, "receive from server:%s\r\n", buf);
    }
    close(cln_socket);
    return 0;
}

void err_handle(char *msg)
{
    fprintf(stderr, "%s\r\n", msg);
    exit(1);
}