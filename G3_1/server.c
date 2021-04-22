#include "head.h"

sqlite3 *db = NULL;  //数据库句柄

void do_login(int sockfd, MSG *pbuf)
{
		char *errmsg;
		char cmd[64];
		char **resultp;
		int pnrow,pncolumn;
		sprintf(cmd,"selete * from user where name = '%s'",pbuf.name);
	   //从数据库中取出用户名和从客户端发送过来的用户名进行比较
	   	if( sqlite3_get_table(db,sql,&resultp,&pnrow,&pncolumn,&errmsg) != SQLITE_OK)
		{
			printf("err:%s\n", errmsg);
			exit(EXIT_FAILURE);
		}
		else
		{
				if(!strcmp(pbuf.password,result[pncolumn]))
				{
					pbuf.ret = SUCCESS;
					send(sockfd,pbuf,sizeof(pbuf),0);
				}
				else
				{
					pbuf.ret = FAILED;
					send(sockfd,pbuf,sizeof(pbuf),0);
				}
		}
		
}

void do_staff_change_passwd(int sockfd, MSG *pbuf)
{
	char *errmsg;
	char cmd[64];
	sprintf(cmd,"update data set passwd = '%s' where name = '%s'",pbuf.passwd,pbuf.name);
	if( sqlite3_exec(db,cmd,NULL,NULL,&errmsg) == SQLITE_OK)
	{
		pbuf.ret = SUCCESS;
		send(sockfd,pbuf,sizeof(pbuf),0);
	}
	else
	{
	pbuf.ret = FAILED;
	send(sockfd,pbuf,sizeof(pbuf),0);	
	}	
}

void do_staff_query(int sockfd, MSG *pbuf)
{
	char *errmsg;
	char cmd[64];
	char **resultp;
	int pnrow,pncolumn;
	sprintf(cmd,"selete from data where name = '%s'",pbuf.name);
    if( sqlite3_get_table(db,cmd,&resultp,&pnrow,&pncolumn,&errmsg) == SQLITE_OK)//如果查询用户成功
	{
   //将查询到的用户的信息放到结构体中
		pbuf.ret = SUCCESS;
		pbuf->info.id = atoi(resultp[10]);
		strcpy(pbuf->info.name,resultp[11]);
		strcpy(pbuf->info.addr,resultp[12]);
		pbuf->info.age = atoi(resultp[13]);
		pbuf->info.salary = atof(resultp[14]);
		
		send(sockfd,pbuf,sizeof(pbuf),0);
	}
	else
	{
		pbuf.ret = FAILED;
		send(sockfd,pbuf,sizeof(pbuf),0);
	}
}

void do_admin_query(int sockfd, MSG *pbuf)
{
	char *errmsg;
	char cmd[64];
	char **resultp;
	int pnrow,pncolumn;
    //pbuf.INFO == 数据库中查询到的id
	//将查询到的用户信息放到结构体中
	pbuf.ret = SUCCESS;
	send(sockfd,pbuf,sizeof(pbuf),0);
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
	//创建表
	sqlite3_exec(db,)

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
