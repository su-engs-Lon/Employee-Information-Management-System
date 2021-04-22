#include "head.h"

sqlite3 *db = NULL;  //数据库句柄

void do_login(int sockfd, MSG *pbuf)
{
   
}

void do_staff_change_passwd(int sockfd, MSG *pbuf)
{
   
}

void do_staff_query(int sockfd, MSG *pbuf)
{
    
}

void do_admin_query(int sockfd, MSG *pbuf)
{
    
}

void *handler(void * arg)
{
     MSG msg;
    int n;
    int connfd = (int)arg;

    while(1)
    {
        n = recv(connfd, &msg, sizeof(MSG), 0);
        //printf("name = %s\n", msg.name);
        if(n == 0){  //客户端退出
            pthread_exit(NULL);
            close(connfd);
        }else if(n > 0){  //收到信息
            //printf("recv type = %d\n", msg.type);
            switch (msg.type) {
            case LOGIN:  //登录
                do_login(connfd, &msg);
                break;
            case STAFF_CHANGE_PASSWD:
                do_staff_change_passwd(connfd, &msg);
                break;
            case STAFF_QUERY:
                do_staff_query(connfd, &msg);
                break;
            case ADMIN_QUERY:
                do_admin_query(connfd, &msg);
                break;
            case ADMIN_DEL_STAFF:
//                do_admin_del(connfd, &msg);
                break;
            case ADMIN_ADD_STAFF:
//                do_admin_add(connfd, &msg);
                break;
            default:
                break;
            }
        }else{
            printf("abc");
            break;
        }
    }
    close(connfd);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    int listenfd, connfd;
    struct sockaddr_in myaddr;

    if (argc < 3)
    {
        printf("Usage : %s <ip> <port>\n", argv[0]);
        exit(-1);
    }

    //打开数据库
    if(sqlite3_open(DATABASE, &db) < 0){
        printf("fail to sqlite3_open : %s\n", sqlite3_errmsg(db));
        return -1;
    }

    //创建服务器socket
    listenfd = socket(PF_INET, SOCK_STREAM, 0);
    if(listenfd < 0){
        perror("fail to socket");
        exit(-1);
    }
    bzero(&myaddr, sizeof(myaddr));
    myaddr.sin_family = PF_INET;
    myaddr.sin_port = htons(atoi(argv[2]));
    myaddr.sin_addr.s_addr = inet_addr(argv[1]);
    if (bind(listenfd, (SA *)&myaddr, sizeof(myaddr)) < 0)
    {
        perror("fail to bind");
        exit(-1);
    }

    // XXX int listen(int sockfd, int backlog);

    //接受客户端请求，创建子线程

}
