#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define CLIENT_NUM 5
#define BUFSIZE 512

void err_handle(char *mesg);
void dump_addrinfo(const struct sockaddr_in *addr);

int main(int argc, char *argv[])
{

    int server_sock = -1;
    int clnt_sock;
    int clnt_addr_sz;
    struct sockaddr_in server_addr;
    struct sockaddr_in clnt_addr;
    int str_len;
    int i;
    char buf[BUFSIZE];
    fprintf(stdout, "hello xptd for echo server\r\n");

    if (argc != 2)
    {
        fprintf(stdout, "Usage:%s <port>\r\n", argv[0]);
        exit(1);
    }

    server_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_sock == -1)
    {
        err_handle("socket() err\r\n");
    }
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[1]));
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        err_handle("bind() err\r\n");
    }

    if (listen(server_sock, CLIENT_NUM) == -1)
    {
        err_handle("listen err\r\n");
    }
    clnt_addr_sz = sizeof(clnt_addr);
    for (i = 0; i < CLIENT_NUM; i++)
    {
        clnt_sock = accept(server_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_sz);
        if (clnt_sock == -1)
        {
            err_handle("accept err\r\n");
        }

        fprintf(stdout, "client[%d]:connected\r\n", i + 1);
        dump_addrinfo(&clnt_addr);

        while ((str_len = read(clnt_sock, buf, BUFSIZE)) != 0)
        {
            write(clnt_sock, buf, str_len);
        }
        close(clnt_sock);
    }

    close(server_sock);
    return 0;
}

void err_handle(char *mesg)
{
    fputs(mesg, stderr);
    fputc('\n', stderr);
    exit(1);
}

void dump_addrinfo(const struct sockaddr_in *addr)
{
    fprintf(stdout, "addr family:%d\r\n", addr->sin_family);
    fprintf(stdout, "port:%d\r\n", ntohs(addr->sin_port));
    fprintf(stdout, "ip:%s\r\n", inet_ntoa(addr->sin_addr));
}