#include "head.h"

sqlite3 *db = NULL;  //数据库句柄

void do_login(int socked, MSG *pbuf)
{
    char *errmsg;
    char **resultp;
    char cmd[256];

    int n_row, n_cloum;

    sprintf(cmd, "select * from usr where name='%s'",pbuf->name);

    puts(cmd);

    if (sqlite3_get_table(db, cmd, &resultp, &n_row, &n_cloum, &errmsg) != SQLITE_OK)
    {
        printf("err:%s\n", errmsg);
        exit(EXIT_FAILURE);
    }

    if(n_row == 0){
        strcpy(pbuf->data, "username or password err");
    }else{
        strcpy(pbuf->data, "ok");
    }

    send(socked, pbuf, sizeof(MSG), 0);
}

void do_staff_change_passwd(int sockfd, MSG *pbuf)
{
	char *errmsg;
	char cmd[256];
	sprintf(cmd,"update data set passwd = '%s' where name = '%s'",pbuf->passwd,pbuf->name);
	// 根据 name 修改数据库内容为 passwd
    if( sqlite3_exec(db,cmd,NULL,NULL,&errmsg) == SQLITE_OK)
	{
		//修改成功 ret = 0，data = “修改密码完成”
		pbuf->ret = -1;
		strcpy(pbuf->data,"修改密码完成");
	}
	else 
	{
		//查询失败 ret = -1, data = "修改密码失败“
		pbuf->ret = 0;
		strcpy(pbuf->data,"修改密码失败");
	}
	send(sockfd,(void *)&pbuf,sizeof(MSG),0);
}

void do_staff_query(int sockfd, MSG *pbuf)
{
    //查找用户信息
	char *errmsg;
	char **user_msg;
	char cmd[256];
	int  n_row,n_cloum;
	sprintf(cmd,"select from data where name = %s",pbuf->name);

    if( sqlite3_get_table(db,cmd,&user_msg,&n_row,&n_cloum,&errmsg) == SQLITE_OK)
	{
		//查询成功 ret = 0，查询到的信息保存在user_msg中
		//数据库顺序： name,passwd,id,trueName,addr,age,salary,level 
		pbuf->ret = -1;
		strcpy(pbuf->data,"获得员工信息成功");
		pbuf->info.id = atoi(user_msg[10]);
		strcpy(pbuf->info.name,user_msg[11]);
		strcpy(pbuf->info.addr,user_msg[12]);
		pbuf->info.age = atoi(user_msg[13]);
		pbuf->info.salary = atof(user_msg[14]);
		pbuf->ret = atoi(user_msg[15]);
	}
	else 
	{
		//查询失败 ret = -1, data = "获得员工信息失败“
		pbuf->ret = 0;
		strcpy(pbuf->data,"获得员工信息成失败");
	}
    //发送 info
	send(sockfd,(void *)&pbuf,sizeof(MSG),0);
}

void do_admin_query(int sockfd, MSG *pbuf)
{
    // 若 data为空 发送当前用户信息
	// 若 data不为空 查询用户并将此用户的信息发送
	if(strcmp(pbuf->data,"") == 0)
	{
		do_staff_query(sockfd,pbuf);
	}
	else
	{
	    char *errmsg;
	    char sql[64] = {'\0'};
	    char **user_msg;
	    int  nrow,ncolumn;
	    sprintf(sql,"select from data where name = %s",pbuf->data);

        if( sqlite3_get_table(db,sql,&user_msg,&nrow,&ncolumn,&errmsg) != SQLITE_OK)
  	    {
		    //查询成功 ret = 0，查询到的信息保存在user_msg中
		    //数据库顺序： name,passwd,id,trueName,addr,age,salary,level 
		    pbuf->ret = -1;
		    strcpy(pbuf->data,"获得员工信息成功");
		    pbuf->info.id = atoi(user_msg[10]);
		    strcpy(pbuf->info.name,user_msg[11]);
		    strcpy(pbuf->info.addr,user_msg[12]);
		    pbuf->info.age = atoi(user_msg[13]);
		    pbuf->info.salary = atof(user_msg[14]);
		    pbuf->ret = atoi(user_msg[15]);
	    }
	    else 
	    {
		    //查询失败 ret = -1, data = "获得员工信息失败“
		    pbuf->ret = 0;
		    strcpy(pbuf->data,"获得员工信息成失败");
	    }
        //发送 info
	    send(sockfd,(void *)&pbuf,sizeof(MSG),0);
    }
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

void data_base_init()
{
	//初始化数据库
	char *errmsg;
    int no;
    char name[64];

	char sql[256] = {"create table usr(level int,passwd text,id int,name text,addr text \
					 age int,salary float)"};
	sqlite3_exec(db,sql,NULL,NULL,&errmsg);
	sqlite3_exec(db,"insert into data values(101,'bat',1000,'Tony','济南',18,8000);",NULL,NULL,&errmsg);
	
}

int main(int argc, char *argv[])
{
    int listenfd, connfd;
    struct sockaddr_in myaddr;
	void*ret;
	pthread_t tid;

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
	
     data_base_init();
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
	if (listen(listenfd, 5) < 0)
    {
        perror("fail to listen");
        exit(-1);
    }
   //接受客户端请求，创建子线程
    
        if((connfd = accept(listenfd, NULL, NULL)) < 0){
            perror("fail to accept");
            exit(-1);
        }
    if(pthread_create(&tid, NULL, handler, &connfd) != 0)
	{
		perror("fail to create");
		exit(1);
	}
	//pthread_join(tid,NULL);
	pthread_join(tid, &ret);
	
}
