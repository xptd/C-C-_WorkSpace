#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define BUFSIZE 512

void err_handle(char *msg);
void dump_addrinfo(const struct sockaddr_in *addr);

int main(int argc, char *argv[])
{
    int clnt_sock = -1;
    struct sockaddr_in server_addr;
    char buf[BUFSIZ];
    int send_len = 0;
    int rec_cnt = 0;
    int rec_len = 0;
    if (argc < 3)
    {
        fprintf(stdout, "Usage: %s <server_ip> <server_port>\r\n", argv[0]);
        exit(1);
    }

    fprintf(stdout, "hello xptd for echo_client\r\n");

    clnt_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clnt_sock == -1)
    {
        err_handle("socket() err\r\n");
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    dump_addrinfo(&server_addr);

    if (connect(clnt_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        err_handle("connect err\r\n");
    }
    fprintf(stdout, "conncted to:%s success!\r\n", inet_ntoa(server_addr.sin_addr));

    while (1)
    {
        memset(buf, 0, BUFSIZE);
        fputs("\r\nPlease input a mssage(q or Q quit):\r\n", stdout);
        fgets(buf, BUFSIZE, stdin);

        if (!strcmp(buf, "q\n") || !strcmp(buf, "Q\n"))
        {
            break;
        }
        send_len = write(clnt_sock, buf, strlen(buf));
        if (send_len == -1)
        {
            err_handle("write() err\r\n");
        }
        while (rec_len < send_len)
        {
            rec_cnt = read(clnt_sock, &buf[rec_len], BUFSIZE - 1);
            if (rec_cnt == -1)
            {
                err_handle("read() err\r\n");
            }
            rec_len += rec_cnt;
        }
        buf[rec_len] = 0;
        fprintf(stdout, "Message from server:%s", buf);
    }
    close(clnt_sock);
    return 0;
}

void err_handle(char *msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}
void dump_addrinfo(const struct sockaddr_in *addr)
{
    fprintf(stdout, "addr family:%d\r\n", addr->sin_family);
    fprintf(stdout, "port:%d\r\n", ntohs(addr->sin_port));
    fprintf(stdout, "ip:%s\r\n", inet_ntoa(addr->sin_addr));
}