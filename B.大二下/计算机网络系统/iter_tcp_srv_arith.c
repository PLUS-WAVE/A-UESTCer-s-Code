#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int sigint_flag = 0; // SIGINT 信号标志

// SIGINT 信号处理函数
void handle_sigint(int sig)
{
    fprintf(stdout, "[srv] SIGINT is coming!\n");
    sigint_flag = 1;
}


// 服务器业务处理函数
void srv_biz(int connfd)
{
    int32_t op;
    int64_t op1, op2, result;
    unsigned char rqt_pdu[sizeof(op) + sizeof(op1) + sizeof(op2)];

    while (1)
    {
        // 读取并解析 RQT PDU
        if (read(connfd, &rqt_pdu, sizeof(rqt_pdu)) <= 0)
        {
            close(connfd);
            break;
        }

        // 从请求报文中获取op，op1和op2，并将它们从网络字节序转换为主机字节序
        memcpy(&op, rqt_pdu, sizeof(op));
        op = ntohl(op);
        memcpy(&op1, rqt_pdu + sizeof(op), sizeof(op1));
        op1 = be64toh(op1);
        memcpy(&op2, rqt_pdu + sizeof(op) + sizeof(op1), sizeof(op2));
        op2 = be64toh(op2);

        const char *ret_op;
        // 根据运算符进行相应的运算
        switch (op) {
            case 0x00000001: result = op1 + op2; ret_op = "+"; break;
            case 0x00000002: result = op1 - op2; ret_op = "-"; break;
            case 0x00000004: result = op1 * op2; ret_op = "*"; break;
            case 0x00000008: result = op1 / op2; ret_op = "/"; break;
            case 0x00000010: result = op1 % op2; ret_op = "%"; break;
            default: result = 0; ret_op = "?";
        }

        // 打印运算结果
        fprintf(stdout, "[rqt_res] %ld %s %ld = %ld\n", op1, ret_op, op2, result);

        // 将运算结果转换为网络字节序
        result = htobe64(result);

        // 将运算结果发送给客户端
        write(connfd, &result, sizeof(result));
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stdout, "Usage: %s <ip_address> <port>\n", argv[0]);
        exit(1);
    }

    char *ip_address = argv[1];
    int port = atoi(argv[2]);

    int listenfd, connfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t cliaddr_len;
    char str[INET_ADDRSTRLEN];

    // 设置 SIGINT 信号处理函数
    struct sigaction sa;
    sa.sa_flags = 0;
    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);

    // 创建 socket
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    // 设置服务器地址
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(ip_address);
    servaddr.sin_port = htons(port);

    // 绑定地址
    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    // 开始监听
    listen(listenfd, 20);

    fprintf(stdout, "[srv] server[%s:%d] is initializing!\n", ip_address, port);

    // 主循环，等待客户端连接
    while (!sigint_flag)
    {
        cliaddr_len = sizeof(cliaddr);
        if (sigint_flag)
        {
            break;
        }
        connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len);
        if (connfd < 0)
        {
            if (errno == EINTR)
            {
                fprintf(stdout, "[srv] listenfd is closed!\n");
                fprintf(stdout, "[srv] server is going to exit!\n");
                break;
            }
            else
            {
                perror("accept error");
                exit(1);
            }
        }

        fprintf(stdout, "[srv] client[%s:%d] is accepted!\n", inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)), ntohs(cliaddr.sin_port));

        // 处理客户端请求
        srv_biz(connfd);

        fprintf(stdout, "[srv] client[%s:%d] is closed!\n", inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)), ntohs(cliaddr.sin_port));


    }

    // 关闭监听 socket
    close(listenfd);

    return 0;
}