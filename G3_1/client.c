#include "head.h"

int do_login(int sockfd, MSG *pbuf)
{
    
}

void do_stuff(int sockfd, MSG *pbuf)
{
    
}

int do_admin(int sockfd, MSG *pbuf)
{
    
}

int main(int argc, char *argv[])
{
    int sockfd, ret;
    struct sockaddr_in servaddr;
    MSG buf;
    char clean[64];

    if (argc < 3)
    {
        printf("Usage : %s <serv_ip> <serv_port>\n", argv[0]);
        exit(-1);
    }

    //创建客户端socket
    if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("fail to socket");
        exit(-1);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = PF_INET;
    servaddr.sin_port = htons(atoi(argv[2]));
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);

    //连接服务器

}
