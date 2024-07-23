#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 128

// 将运算符从字符串转换为对应的编号
int32_t op_to_int(const char *op)
{
    if (strcmp(op, "ADD") == 0) return 0x00000001;
    if (strcmp(op, "SUB") == 0) return 0x00000002;
    if (strcmp(op, "MUL") == 0) return 0x00000004;
    if (strcmp(op, "DIV") == 0) return 0x00000008;
    if (strcmp(op, "MOD") == 0) return 0x00000010;
    return -1;
}

// 将运算符从编号转换为对应的字符串
const char* int_to_op(int32_t op)
{
    switch(op)
    {
        case 0x00000001: return "+";
        case 0x00000002: return "-";
        case 0x00000004: return "*";
        case 0x00000008: return "/";
        case 0x00000010: return "%";
        default: return "?";
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <ip_address> <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *SERVER_IP = argv[1];
    int PORT = atoi(argv[2]);

    int sockfd;
    struct sockaddr_in serv_addr;

    // 创建套接字
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // 设置服务器地址结构
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    serv_addr.sin_port = htons(PORT);

    // 连接到服务器
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    // 输出已连接的服务器信息
    fprintf(stdout, "[cli] server[%s:%d] is connected!\n", SERVER_IP, PORT);

    int32_t op;
    int64_t op1, op2, result;
    char op_str[4];

    // 主循环
    while (1)
    {
        // 读取用户输入
        scanf("%s %ld %ld", op_str, &op1, &op2);

        // 检查用户是否想要退出
        if (strcmp(op_str, "EXIT") == 0)
        {
            fprintf(stdout, "[cli] command EXIT received\n");
            break;
        }

        // 将运算符从字符串转换为对应的编号
        op = op_to_int(op_str);
        const char* op_result = int_to_op(op);
        int64_t op1_result = op1;
        int64_t op2_result = op2;
        
        // 转换为网络字节序
        int32_t op_n = htonl(op);
        int64_t op1_n = htobe64(op1);
        int64_t op2_n = htobe64(op2);

        // 创建一个字节数组来存储请求报文
        unsigned char rqt_pdu[sizeof(op_n) + sizeof(op1_n) + sizeof(op2_n)];

        // 将op，op1和op2复制到请求报文中
        memcpy(rqt_pdu, &op_n, sizeof(op_n));
        memcpy(rqt_pdu + sizeof(op_n), &op1_n, sizeof(op1_n));
        memcpy(rqt_pdu + sizeof(op_n) + sizeof(op1_n), &op2_n, sizeof(op2_n));

        write(sockfd, &rqt_pdu, sizeof(rqt_pdu));

        // 从服务器接收响应
        if (read(sockfd, &result, sizeof(result)) == -1)
        {
            // 服务器端已关闭连接，关闭客户端的连接
            close(sockfd);
            fprintf(stdout, "[cli] connfd is closed!\n");
            fprintf(stdout, "[cli] client is going to exit!\n");
            exit(EXIT_FAILURE);
        }

        // 将服务器响应转换为主机字节序
        result = be64toh(result);
        
        // 输出服务器响应
        fprintf(stdout, "[rep_rcv] %ld %s %ld = %ld\n", op1_result, op_result, op2_result, result);
    }

    // 关闭套接字
    close(sockfd);
    fprintf(stdout, "[cli] connfd is closed!\n");
    fprintf(stdout, "[cli] client is going to exit!\n");

    return 0;
}