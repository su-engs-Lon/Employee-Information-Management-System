#include "head.h"

int do_login(int sockfd, MSG *pbuf)
{
	while(1)
	{
    puts("please input your name: ");         //让用户输入用户名和密码
	fgets(buf.name,N,stdin);
	puts("please input your passwd\n");
	fgets(buf.passwd,N,stdin);
	send(sockfd,pbuf,sizeof(pbuf),0);         //发送用户名密码给服务端，让服务端判断用户名密码是否匹配    
	nbytes = recv(sockfd, pbuf, sizeof(pbuf), 0);         //接收服务端发送来的ret
        if(nbytes < 0){
            perror("recv err");
            exit(-1);
        }
		else if (nbytes > 0)
		{
           if(pbuf.ret == 0)                  //判断ret是0 or 1 如果是0,则不匹配；反之，显示登录成功
		   {
			   puts("name and passwd does not match");
			   continue;
		   }
		   else if(pbuf.ret == 1)
		   {
			   puts(login success!\n);
			   return 1;
		   }
		} 
		else
		{
            printf("peer exit\n");
            break;
        }
	}
	
		
}
	

void do_stuff(int sockfd, MSG *pbuf)
{
	int option;
	while(1)
	{
	printf("--------you are stuff----------\n");
	printf("-----1.STAFF_CHANGE_PASSWD-----\n");
	printf("-----2.STAFF_QUERY        -----\n");
	printf("-----3.STAFF_EXIT         -----\n");
	printf("please choose your operating:");
	scanf("%d",&option);
	switch(option)
	{
		case 1:
				printf(please input your new passwd:);
				fgets(pbuf.passwd,N,stdin);
				pbuf.type = STAFF_CHANGE_PASSWD;
				send(sockfd,pbuf,sizeof(pbuf),0);
				recv(sockfd,pbuf,sizeof(pbuf),0);
				if(pbuf.ret == SUCCESS)
				{
					printf("operate success!\n");
					continue;
				}
				else
				{
					puts("operate failed!\n");
					continue;
				}
				break;
		case 2:printf("please input query id:");
			   scanf("%d",pbuf.info.id);
			   pbuf.type = STAFF_QUERY;
			   send(sockfd,pbuf,sizeof(pbuf),0);
			   recv(sockfd,pbuf,sizeof(pbuf),0);
			   if(pbuf.ret == SUCCESS)
			   {
			   printf("id = %d,name = %s,addr = %s,age = %d,salary = %.1f\n",pbuf.id,pbuf.name,pbuf.addr,pbuf.age,pbuf.salary);
			   }
			   else
			   {
				   printf("query is failed\n");
			   }
			   break;
		
		case 3:
				break;
				
	}
	break;
	}
}

int do_admin(int sockfd, MSG *pbuf)
{
    int option;
	while(1)
	{
	printf("--------you are admin----------\n");
	printf("-----  1.ADMIN_QUERY     -----\n");
	printf("-----  2.ADMIN_ADD_STAFF  -----\n");
	printf("-----  3.ADMIN_DEL_STAFF  -----\n");
	printf("-----  4.ADMIN_EXIT       -----\n");

	printf("please choose your operating:");
	scanf("%d",&option);
	switch(option)
	{
		case 1:
				printf(please input query id:);
				fgets(pbuf.info.id,N,stdin);
				pbuf.type = ADMIN_QUERY;
				send(sockfd,pbuf,sizeof(pbuf),0);
				recv(sockfd,pbuf,sizeof(pbuf),0);
				if(pbuf.ret == SUCCESS)
				{
					printf("id = %d,name = %s,addr = %s,age = %d,salary = %.1f\n",pbuf.INFO.id,pbuf.INFO.name,pbuf.INFO.addr,pbuf.INFO.age,pbuf.INFO.salary);
					continue;
				}
				else
				{
					puts("operate failed!\n");
					continue;
				}
				break;
		case 2:printf("please input user information:");
			   puts("passwd = ");
			   scanf("%d",pbuf.passwd);
			   puts("id = ");
			   scanf("%d",pbuf.info.id);
			   puts("name = ");
			   scanf("%s",pbuf.info.name);
			   puts("addr = ");
			   scanf("%s",pbuf.info.addr);
			   puts("age = ");
			   scanf("%d",pbuf.info.age);
			   puts("salary = ");
			   scanf("%f",pbuf.info.salary);
			   pbuf.type = ADMIN_ADD_STAFF;
			   send(sockfd,pbuf,sizeof(pbuf),0);
			   recv(sockfd,pbuf,sizeof(pbuf),0);
			   if(pbuf.ret == SUCCESS)
			   {
				   printf("add user success!\n");
			   }
			   else
			   {
				   printf("add user failed!\n");
			   }
			   break;
		case 3:printf("please input delete id:");
			   scanf("%d",pbuf.info.id);
			   pbuf.type = ADMIN_DEL_STAFF;
			   send(sockfd,pbuf,sizeof(pbuf),0);
			   recv(sockfd,pbuf,sizeof(pbuf),0);
			   if(pbuf.ret == SUCCESS)
			   {
			   printf("delete user success!\n");
			   }
			   else
			   {
				   printf("delete user failed!\n");
			   }
			   break;
		
		case 4:
				break;
				
	}
	break;
	}
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

	if(connect(sockfd, (struct sockaddr *)&serveraddr, addrlen) < 0){
        perror("connect err");
        exit(-1);
    }
	
	printf("----welcome to employee management system----");
	printf("---------------please login!-----------------");
	do_login(sockfd,buf);
	if(buf.info.id < 10)
	{
		do_admin(sockfd,buf);
	}
	else
	{
		do_stuff(sockfd,buf);
	}
	return 0;
}
