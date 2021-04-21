#include "head.h"

int do_login(int sockfd, MSG *pbuf)
{
	while(1)
	{
		puts("please input your name");

		scanf("%s",pbuf->info.name);
		puts("please input your passwd");
		scanf("%s",pbuf->passwd);
		pbuf->type=LOGIN;
		send(sockfd, pbuf, sizeof(MSG), 0);
		recv(sockfd, pbuf,sizeof(MSG), 0);
		puts(pbuf->data);

		if(pbuf->ret)//ret==1代表操作结果错误
		{
			puts("登入失败，继续登入输入y,退出输入n");
			char c;
			getchar();
			scanf("%c",&c);
			if(c=='y')
				continue;
			else
				exit(0);
		}
		else
			break;
	} 
	return pbuf->USER_LEVEL;
}
//增加员工的函数
void do_add_stuff(int sockfd,MSG *pbuf)
{
	puts("please input stuff id");
	scanf("%d",&pbuf->info.id);
	puts("please input stuff name");
	getchar();
	gets(pbuf->info.name);
	puts("please input stuff addr");
	// getchar();
	gets(pbuf->info.addr);
	puts("please input stuff age");
	scanf("%d",&pbuf->info.age);
	puts("please input stuff salary");
	scanf("%d",&pbuf->info.salary);

	puts("please input stuff USER_LEVEL");
	scanf("%d",&pbuf->USER_LEVEL);
	puts("please input stuff passwd");
	getchar();
	gets(pbuf->passwd);                                                                                         
	printf("员工信息为:%d,%s,%s,%d,%d\n",pbuf->info.id,pbuf->info.name,pbuf->info.addr,pbuf->info.age,pbuf->info.salary); 
	pbuf->type=ADMIN_ADD_STAFF;

	send(sockfd, pbuf, sizeof(MSG), 0);
	recv(sockfd, pbuf,sizeof(MSG), 0);
	puts(pbuf->data);
}
//减少员工的函数
void do_del_stuff(int sockfd,MSG *pbuf)
{
	puts("please input stuff name");
	getchar();
	gets(pbuf->info.name);

	pbuf->type=ADMIN_DEL_STAFF;

	send(sockfd, pbuf, sizeof(MSG), 0);
	recv(sockfd, pbuf,sizeof(MSG), 0);
	puts(pbuf->data);
}
//管理员查询的函数
void do_query_admin(int sockfd,MSG *pbuf)
{
	puts("please input stuff name");
	getchar();
	gets(pbuf->info.name);

	pbuf->type=ADMIN_QUERY;

	send(sockfd, pbuf,sizeof(MSG), 0);
	recv(sockfd, pbuf,sizeof(MSG), 0);
	puts(pbuf->data);

	if(pbuf->ret==0)
	printf("员工信息为:%d,%s,%s,%d,%d\n",pbuf->info.id,pbuf->info.name,pbuf->info.addr,pbuf->info.age,pbuf->info.salary); 
}
void do_admin(int sockfd, MSG *pbuf)
{ 
	while(1)
	{
		printf("-----------------------\n");
		printf("3-增加员工  ");                          //管理员增加员工
		printf("4-删除员工\n");                          //管理员删除员工
		printf("5-查询      ");                              //管理员查询
		printf("6-退出\n");                                      //退出
		printf("请选择操作项:");
		// gets(pbuf->type);
		scanf("%d",&pbuf->type);
		switch(pbuf->type)
		{
		case ADMIN_ADD_STAFF :
			//增加员工的函数
			do_add_stuff(sockfd,pbuf);
			break;
		case ADMIN_DEL_STAFF :
			//减少员工的函数
			do_del_stuff(sockfd,pbuf);
			break;
		case ADMIN_QUERY :
			//管理员查询的函数
			do_query_admin(sockfd,pbuf);
			break;
		case QUIT :
			close(sockfd);
			exit (0);
		}
	}
}
//员工改密码的函数
void staff_change_passwd(int sockfd,MSG *pbuf)
{
	//puts("please input your name");
	//getchar();
	//gets(pbuf->info.name);
	puts("please input new password");
	getchar();
	gets(pbuf->passwd);
	pbuf->type=STAFF_CHANGE_PASSWD;

	send(sockfd, pbuf, sizeof(MSG), 0);
	recv(sockfd, pbuf,sizeof(MSG), 0);
	puts(pbuf->data);
}
//员工查询
void do_query_stuff(int sockfd,MSG *pbuf)
{
	pbuf->type=STAFF_QUERY;
	send(sockfd, pbuf, sizeof(MSG), 0);
	recv(sockfd, pbuf,sizeof(MSG), 0);
	puts(pbuf->data);
	printf("员工信息为:%d,%s,%s,%d,%d\n",pbuf->info.id,pbuf->info.name,pbuf->info.addr,pbuf->info.age,pbuf->info.salary); 
}

int do_stuff(int sockfd, MSG *pbuf)
{
	while(1)
	{ 
		puts("please input a number represent a common");
		puts("1-STAFF_CHANGE_PASSWD");                    //修改密码
		puts("2-STAFF_QUERY");                            //员工查询
		puts("6-QUIT");                                   //退出  	

		//gets(pbuf->type);
		scanf("%d",&pbuf->type);
		switch(pbuf->type)
		{
		case STAFF_CHANGE_PASSWD :
			//员工改密码的函数
			staff_change_passwd(sockfd,pbuf);
			break;
		case STAFF_QUERY :
			//员工查询
			do_query_stuff(sockfd,pbuf);
			break;
		case QUIT :
			close(sockfd);
			exit (0);
		}
	}		
}

int main(int argc, char *argv[])
{
	int sockfd, ret;
	struct sockaddr_in servaddr;
	MSG buf;
	int addrlen = sizeof(struct sockaddr);
	char clean[64];
	pid_t pid;

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
	if(connect(sockfd, (struct sockaddr *)&servaddr, addrlen) < 0){
		perror("connect err");
		exit(-1);
	}

	ret=do_login(sockfd,&buf);

	switch(ret){
	case STAFF://代表普通员工
		do_stuff(sockfd, &buf);
		break;

	case ADMIN://代表管理员
		do_admin(sockfd, &buf);
		break;						
	}
	close(sockfd);
	return 0;

}
