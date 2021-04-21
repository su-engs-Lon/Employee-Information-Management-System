#include "head.h"

sqlite3 *db = NULL;  //数据库句柄

void do_login(int socked, MSG *pbuf)
{
    char *errmsg;
    char **resultp;
<<<<<<< HEAD
	
=======
<<<<<<< HEAD
	
=======
>>>>>>> fc9cad3396246ffc08aa7922d0ecdc11da9b3858
>>>>>>> 2cde025e68fdf43a297d0d8e805aec039f81fe1d
    char cmd[256];

    int n_row, n_cloum;

<<<<<<< HEAD
    sprintf(cmd, "select * from usr where name='%s'",pbuf->info.name);
=======
<<<<<<< HEAD
    sprintf(cmd, "select * from usr where name='%s'",pbuf->info.name);
=======
    sprintf(cmd, "select * from usr where name='%s'",pbuf->name);

    puts(cmd);
>>>>>>> fc9cad3396246ffc08aa7922d0ecdc11da9b3858
>>>>>>> 2cde025e68fdf43a297d0d8e805aec039f81fe1d

    if (sqlite3_get_table(db, cmd, &resultp, &n_row, &n_cloum, &errmsg) != SQLITE_OK)
    {
        printf("err:%s\n", errmsg);
        exit(EXIT_FAILURE);
    }

    if(n_row == 0){
<<<<<<< HEAD
		printf("-------------------------------------------------\n");
        strcpy(pbuf->data, "username or password err");
		pbuf->ret=1;
    }
	else
	{
		if(strcmp(pbuf->passwd,resultp[8])==0)
		{
			strcpy(pbuf->data,"登入成功");
			pbuf->ret=0;
			pbuf->USER_LEVEL = atoi(resultp[7]);
		}
		else
		{
			strcpy(pbuf->data, "登入失败");
			pbuf->ret=1;
		}
=======
<<<<<<< HEAD
		printf("-------------------------------------------------\n");
        strcpy(pbuf->data, "username or password err");
		pbuf->ret=1;
    }
	else
	{
		if(strcmp(pbuf->passwd,resultp[8])==0)
		{
			strcpy(pbuf->data,"登入ok");
			pbuf->ret=0;
			pbuf->USER_LEVEL = atoi(resultp[7]);
		}
		else
		{
			strcpy(pbuf->data, "登入err");
			pbuf->ret=1;
		}
=======
        strcpy(pbuf->data, "username or password err");
    }else{
        strcpy(pbuf->data, "ok");
>>>>>>> fc9cad3396246ffc08aa7922d0ecdc11da9b3858
>>>>>>> 2cde025e68fdf43a297d0d8e805aec039f81fe1d
    }

    send(socked, pbuf, sizeof(MSG), 0);
}

void do_staff_change_passwd(int sockfd, MSG *pbuf)
{
	char *errmsg;
	char cmd[256];
<<<<<<< HEAD
	sprintf(cmd,"update usr set passwd = \"%s\" where name = \"%s\"",pbuf->passwd,pbuf->info.name);
=======
<<<<<<< HEAD
	sprintf(cmd,"update usr set passwd = \"%s\" where name = \"%s\"",pbuf->passwd,pbuf->info.name);
=======
	sprintf(cmd,"update data set passwd = '%s' where name = '%s'",pbuf->passwd,pbuf->name);
>>>>>>> fc9cad3396246ffc08aa7922d0ecdc11da9b3858
>>>>>>> 2cde025e68fdf43a297d0d8e805aec039f81fe1d
	// 根据 name 修改数据库内容为 passwd
    if( sqlite3_exec(db,cmd,NULL,NULL,&errmsg) == SQLITE_OK)
	{
		//修改成功 ret = 0，data = “修改密码完成”
<<<<<<< HEAD
		pbuf->ret = 0;
=======
<<<<<<< HEAD
		pbuf->ret = 0;
=======
		pbuf->ret = -1;
>>>>>>> fc9cad3396246ffc08aa7922d0ecdc11da9b3858
>>>>>>> 2cde025e68fdf43a297d0d8e805aec039f81fe1d
		strcpy(pbuf->data,"修改密码完成");
	}
	else 
	{
<<<<<<< HEAD
		//查询失败 ret = 1, data = "修改密码失败“
		pbuf->ret = 1;
		strcpy(pbuf->data,"修改密码失败");
	}
	send(sockfd,pbuf,sizeof(MSG),0);
=======
<<<<<<< HEAD
		//查询失败 ret = 1, data = "修改密码失败“
		pbuf->ret = 1;
		strcpy(pbuf->data,"修改密码失败");
	}
	send(sockfd,pbuf,sizeof(MSG),0);
=======
		//查询失败 ret = -1, data = "修改密码失败“
		pbuf->ret = 0;
		strcpy(pbuf->data,"修改密码失败");
	}
	send(sockfd,(void *)&pbuf,sizeof(MSG),0);
>>>>>>> fc9cad3396246ffc08aa7922d0ecdc11da9b3858
>>>>>>> 2cde025e68fdf43a297d0d8e805aec039f81fe1d
}

void do_staff_query(int sockfd, MSG *pbuf)
{
    //查找用户信息
	char *errmsg;
	char **user_msg;
	char cmd[256];
	int  n_row,n_cloum;
<<<<<<< HEAD
	sprintf(cmd,"select * from usr where name = \"%s\"",pbuf->info.name);
=======
<<<<<<< HEAD
	sprintf(cmd,"select * from usr where name = \"%s\"",pbuf->info.name);
=======
	sprintf(cmd,"select from data where name = %s",pbuf->name);
>>>>>>> fc9cad3396246ffc08aa7922d0ecdc11da9b3858
>>>>>>> 2cde025e68fdf43a297d0d8e805aec039f81fe1d

    if( sqlite3_get_table(db,cmd,&user_msg,&n_row,&n_cloum,&errmsg) == SQLITE_OK)
	{
		//查询成功 ret = 0，查询到的信息保存在user_msg中
		//数据库顺序： name,passwd,id,trueName,addr,age,salary,level 
<<<<<<< HEAD
		pbuf->ret = 0;
=======
<<<<<<< HEAD
		pbuf->ret = 0;
		strcpy(pbuf->data,"获得员工信息成功");
		pbuf->info.id = atoi(user_msg[9]);
		strcpy(pbuf->info.name,user_msg[10]);
		strcpy(pbuf->info.addr,user_msg[11]);
		pbuf->info.age = atoi(user_msg[12]);
		pbuf->info.salary = atof(user_msg[13]);
	}
	else 
	{
		//查询失败 ret = 1, data = "获得员工信息失败“
		pbuf->ret = 1;
		strcpy(pbuf->data,"获得员工信息成失败");
	}
    //发送 info
	send(sockfd,pbuf,sizeof(MSG),0);
=======
		pbuf->ret = -1;
>>>>>>> 2cde025e68fdf43a297d0d8e805aec039f81fe1d
		strcpy(pbuf->data,"获得员工信息成功");
		pbuf->info.id = atoi(user_msg[9]);
		strcpy(pbuf->info.name,user_msg[10]);
		strcpy(pbuf->info.addr,user_msg[11]);
		pbuf->info.age = atoi(user_msg[12]);
		pbuf->info.salary = atoi(user_msg[13]);
	}
	else 
	{
		//查询失败 ret = 1, data = "获得员工信息失败“
		pbuf->ret = 1;
		strcpy(pbuf->data,"获得员工信息成失败");
	}
    //发送 info
<<<<<<< HEAD
	send(sockfd,pbuf,sizeof(MSG),0);
=======
	send(sockfd,(void *)&pbuf,sizeof(MSG),0);
>>>>>>> fc9cad3396246ffc08aa7922d0ecdc11da9b3858
>>>>>>> 2cde025e68fdf43a297d0d8e805aec039f81fe1d
}

void do_admin_query(int sockfd, MSG *pbuf)
{
<<<<<<< HEAD
	char *errmsg;
	char cmd[256];
	char **user_msg;
	int  nrow,ncolumn;
	//通过比较名字得到内容
	sprintf(cmd,"select * from usr where name = \"%s\"",pbuf->info.name);

	if( sqlite3_get_table(db,cmd,&user_msg,&nrow,&ncolumn,&errmsg) == SQLITE_OK)
=======
<<<<<<< HEAD

=======
    // 若 data为空 发送当前用户信息
	// 若 data不为空 查询用户并将此用户的信息发送
	if(strcmp(pbuf->data,"") == 0)
>>>>>>> 2cde025e68fdf43a297d0d8e805aec039f81fe1d
	{
		if(nrow==0)
		{
			pbuf->ret=1;
			strcpy(pbuf->data,"无此人");
		}else{
		//查询成功 ret = 0，查询到的信息保存在user_msg中
		//数据库顺序：level,passwd,id,name,addr,age,salary
		pbuf->ret = 0;
		strcpy(pbuf->data,"获得员工信息成功");
		pbuf->info.id = atoi(user_msg[9]);
		strcpy(pbuf->info.name,user_msg[10]);
		strcpy(pbuf->info.addr,user_msg[11]);
		pbuf->info.age = atoi(user_msg[12]);
		pbuf->info.salary = atoi(user_msg[13]);}
	}
	else 
	{
<<<<<<< HEAD
		//查询失败 ret = 1, data = "获得员工信息失败“
		pbuf->ret = 1;
		strcpy(pbuf->data,"获得员工信息失败");
	}
	//发送 info
	send(sockfd,pbuf,sizeof(MSG),0);
=======
>>>>>>> fc9cad3396246ffc08aa7922d0ecdc11da9b3858
	    char *errmsg;
	    char cmd[256];
	    char **user_msg;
	    int  nrow,ncolumn;
<<<<<<< HEAD
		//通过比较名字得到内容
	    sprintf(cmd,"select * from usr where name = \"%s\"",pbuf->info.name);

        if( sqlite3_get_table(db,cmd,&user_msg,&nrow,&ncolumn,&errmsg) == SQLITE_OK)
  	    {
		    //查询成功 ret = 0，查询到的信息保存在user_msg中
		    //数据库顺序：level,passwd,id,name,addr,age,salary
		    pbuf->ret = 0;
		    strcpy(pbuf->data,"获得员工信息成功");
		    pbuf->info.id = atoi(user_msg[9]);
		    strcpy(pbuf->info.name,user_msg[10]);
		    strcpy(pbuf->info.addr,user_msg[11]);
		    pbuf->info.age = atoi(user_msg[12]);
		    pbuf->info.salary = atof(user_msg[13]);
	    }
	    else 
	    {
		    //查询失败 ret = 1, data = "获得员工信息失败“
		    pbuf->ret = 1;
		    strcpy(pbuf->data,"获得员工信息失败");
	    }
        //发送 info
	    send(sockfd,pbuf,sizeof(MSG),0);
    
=======
	    sprintf(cmd,"select from data where name = %s",pbuf->data);

        if( sqlite3_get_table(db,cmd,&user_msg,&nrow,&ncolumn,&errmsg) != SQLITE_OK)
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
>>>>>>> 2cde025e68fdf43a297d0d8e805aec039f81fe1d
}

void do_admin_add(int sockfd, MSG *pbuf)
{
	char *errmsg;
	char cmd[256];
	char **user_msg;
	int nrow = 0,ncolumn = 0;

	sprintf(cmd,"insert into usr values(\"%d\",\"%s\",\"%d\",\"%s\",\
		\"%s\",\"%d\",\"%d\")",pbuf->USER_LEVEL,pbuf->passwd,pbuf->info.id,\
		pbuf->info.name,pbuf->info.addr,pbuf->info.age,\
		pbuf->info.salary);
	if(sqlite3_exec(db,cmd,NULL,NULL,&errmsg) == SQLITE_OK)
	{
		pbuf->ret = 0;
		printf("success to add\n");
		strcpy(pbuf->data,"添加成功");

	}else
	{
		pbuf->ret = 1;
		printf("fail to add");
		strcpy(pbuf->data,"添加失败");
	}

	send(sockfd,pbuf,sizeof(MSG),0);
}

void do_admin_del(int sockfd, MSG *pbuf)
{
	//查询usr用户 从数据库删
	char *errmsg;
	char cmd[256];
	//通过名字查找内容
	sprintf(cmd,"delete from usr where name = \"%s\"",pbuf->info.name);
	//数据库删除操作
	if( sqlite3_exec(db,cmd,NULL,NULL,&errmsg) == SQLITE_OK)
	{
		//删除成功 ret = 0，data = “删除成功”
		pbuf->ret = 0;
		strcpy(pbuf->data,"删除成功");
	}
	else 
	{
		//删除失败 ret = -1, data = "删除失败“
		pbuf->ret = 1;

		strcpy(pbuf->data,"删除失败");
	}
	//将登录的结果反馈给用户端
<<<<<<< HEAD
=======
	send(sockfd,(void *)&pbuf,sizeof(MSG),0);
>>>>>>> fc9cad3396246ffc08aa7922d0ecdc11da9b3858
}

void do_admin_add(int sockfd, MSG *pbuf)
{
	char *errmsg;
	char cmd[256];
	char **user_msg;
	int nrow = 0,ncolumn = 0;
	   
	sprintf(cmd,"insert into usr values(\"%d\",\"%s\",\"%d\",\"%s\",\
					 \"%s\",\"%d\",\"%f\")",pbuf->USER_LEVEL,pbuf->passwd,pbuf->info.id,\
					 pbuf->info.name,pbuf->info.addr,pbuf->info.age,\
					 pbuf->info.salary);
		if(sqlite3_exec(db,cmd,NULL,NULL,&errmsg) == SQLITE_OK)
		{
			pbuf->ret = 0;
			printf("success to add\n");
			strcpy(pbuf->data,"添加成功了");
		
		}else
		{
		    pbuf->ret = 1;
			printf("fail to add");
			strcpy(pbuf->data,"添加失败了");
		}
	
	send(sockfd,pbuf,sizeof(MSG),0);
}

void do_admin_del(int sockfd, MSG *pbuf)
{
	//查询usr用户 从数据库删
	char *errmsg;
	char cmd[256];
	//通过名字查找内容
	sprintf(cmd,"delete from usr where name = \"%s\"",pbuf->info.name);
	//数据库删除操作
	if( sqlite3_exec(db,cmd,NULL,NULL,&errmsg) == SQLITE_OK)
	{
		//删除成功 ret = 0，data = “删除成功”
		pbuf->ret = 0;
		strcpy(pbuf->data,"删除成功");
	}
	else 
	{
		//删除失败 ret = -1, data = "删除失败“
		pbuf->ret = 1;

		strcpy(pbuf->data,"删除失败");
	}
	//将登录的结果反馈给用户端
>>>>>>> 2cde025e68fdf43a297d0d8e805aec039f81fe1d
	send(sockfd,pbuf,sizeof(MSG),0);
}

void *handler(void * arg)
{
<<<<<<< HEAD
	MSG msg;
	int n;
	int connfd;
	connfd = *(int*)arg;

	while(1)
	{
		n = recv(connfd, &msg, sizeof(MSG), 0);
		printf("name = %s\n", msg.info.name);
		if(n == 0){  //客户端退出
			pthread_exit(NULL);
=======
     MSG msg;
    int n;
    int connfd;
	connfd = *(int*)arg;

	printf("进入线程");
    while(1)
    {
        n = recv(connfd, &msg, sizeof(MSG), 0);
        printf("name = %s\n", msg.info.name);
        if(n == 0){  //客户端退出
            pthread_exit(NULL);
>>>>>>> 2cde025e68fdf43a297d0d8e805aec039f81fe1d
            close(connfd);
        }else if(n > 0){  //收到信息
            printf("recv type = %d\n", msg.type);
            switch (msg.type) {
            case LOGIN:  //登录

                do_login(connfd, &msg);
                break;
            case STAFF_CHANGE_PASSWD:
                do_staff_change_passwd(connfd, &msg);
                break;
            case STAFF_QUERY:
<<<<<<< HEAD
				do_staff_query(connfd, &msg);
				break;
			case ADMIN_QUERY:				
				do_admin_query(connfd, &msg);
				break;
			case ADMIN_DEL_STAFF:
				do_admin_del(connfd, &msg);
				break;
			case ADMIN_ADD_STAFF:
				do_admin_add(connfd, &msg);
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
=======
                do_staff_query(connfd, &msg);
                break;
            case ADMIN_QUERY:				
                do_admin_query(connfd, &msg);
                break;
            case ADMIN_DEL_STAFF:
<<<<<<< HEAD
				printf("进入减少前");
              do_admin_del(connfd, &msg);
                break;
            case ADMIN_ADD_STAFF:
				
				printf("进入add前");
              do_admin_add(connfd, &msg);
			  printf("进入del后");
=======
              do_admin_del(connfd, &msg);
                break;
            case ADMIN_ADD_STAFF:
              do_admin_add(connfd, &msg);
>>>>>>> fc9cad3396246ffc08aa7922d0ecdc11da9b3858
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
>>>>>>> 2cde025e68fdf43a297d0d8e805aec039f81fe1d
}

void data_base_init()
{
	//初始化数据库
	char *errmsg;
    int no;
    char name[64];

<<<<<<< HEAD
	char sql[256] = {"create table usr(level int,passwd text,id int,name text,addr text ,age int,salary int);"};
	sqlite3_exec(db,sql,NULL,NULL,&errmsg);
	sqlite3_exec(db,"insert into usr values(101,'bat',1000,'Tony','济南',18,8000);",NULL,NULL,&errmsg);
=======
<<<<<<< HEAD
	char sql[256] = {"create table usr(level int,passwd text,id int,name text,addr text ,age int,salary float);"};
	sqlite3_exec(db,sql,NULL,NULL,&errmsg);
	sqlite3_exec(db,"insert into usr values(101,'bat',1000,'Tony','济南',18,8000);",NULL,NULL,&errmsg);
=======
	char sql[256] = {"create table usr(level int,passwd text,id int,name text,addr text \
					 age int,salary float)"};
	sqlite3_exec(db,sql,NULL,NULL,&errmsg);
	sqlite3_exec(db,"insert into data values(101,'bat',1000,'Tony','济南',18,8000);",NULL,NULL,&errmsg);
>>>>>>> fc9cad3396246ffc08aa7922d0ecdc11da9b3858
	
>>>>>>> 2cde025e68fdf43a297d0d8e805aec039f81fe1d
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
	if(listenfd < 0)
	{
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
	if (listen(listenfd, 5) < 0)
<<<<<<< HEAD
=======
    {
        perror("fail to listen");
        exit(-1);
<<<<<<< HEAD
	}
	//接受客户端请求，创建子线程
	while(1){
		if((connfd = accept(listenfd, NULL, NULL)) < 0){
			perror("fail to accept");
			exit(-1);
		}
		if(pthread_create(&tid, NULL, handler, &connfd) != 0)
		{
			perror("fail to create");
			exit(1);
		}
	}
	//pthread_join(tid,NULL);
	//	pthread_join(tid, &ret);
=======
    }
   //接受客户端请求，创建子线程
    
        if((connfd = accept(listenfd, NULL, NULL)) < 0){
            perror("fail to accept");
            exit(-1);
        }
    if(pthread_create(&tid, NULL, handler, &connfd) != 0)
>>>>>>> 2cde025e68fdf43a297d0d8e805aec039f81fe1d
	{
		perror("fail to listen");
		exit(-1);
	}
	//接受客户端请求，创建子线程
	while(1)
	{
		if((connfd = accept(listenfd, NULL, NULL)) < 0)
		{
			perror("fail to accept");
			exit(-1);
		}
		if(pthread_create(&tid, NULL, handler, &connfd) != 0)
		{
			perror("fail to create");
			exit(1);
		}
	}
<<<<<<< HEAD
=======
	//pthread_join(tid,NULL);
	pthread_join(tid, &ret);
	
>>>>>>> fc9cad3396246ffc08aa7922d0ecdc11da9b3858
>>>>>>> 2cde025e68fdf43a297d0d8e805aec039f81fe1d
}
