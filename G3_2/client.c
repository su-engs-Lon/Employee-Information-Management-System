#include "head.h"


int do_login(int sockfd, MSG *pbuf)
{
	while(1)
	{
		puts("please input your name");
	    gets(buf.name);
	    puts("please input your passwd");
	    gets(buf.passwd);
	    *pbuf.type=LOGIN;
		
		send(sockfd, pbuf, sizeof(MSG), 0);
		recv(clientfd, pbuf,sizeof(MSG), 0);
		puts(*pbuf.data);
		
		if(*pbuf.ret)
		 
			continue;
		else
			break;
		
		
	}
	
	
    
	return *pbuf.USER_LEVEL;
	
}

void do_admin(int sockfd, MSG *pbuf)
{   while(1)
    {
        puts("please input a number represent a common,"
	                                               "3-ADMIN_ADD_STAFF"   //管理员增加员工
                                                   "4-ADMIN_DEL_STAFF"    //管理员删除员工
                                                   "5-ADMIN_QUERY");     //管理员退出
	    gets(*pbuf.type);
	    send(sockfd, pbuf, sizeof(MSG), 0);
		recv(clientfd, pbuf,sizeof(MSG), 0);
			puts(*pbuf.ret);
			puts(*pbut.data);		
		
	}
	
	
}

int do_stuff(int sockfd, MSG *pbuf)
{
    puts("please input a number represent a common,1-STAFF_CHANGE_PASSWD"//修改密码
                                                   " 2-STAFF_QUERY"       //退出
	                                        "6-SUCCESS" );	
	while(1)
	{
    gets(*pbuf.type);
	send(sockfd, pbuf, sizeof(MSG), 0);
	recv(clientfd, pbuf,sizeof(MSG), 0);
    puts(*pbuf.ret);
	puts(*pbut.data);
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
	
	USER_LEVEL=do_login(int sockfd, MSG *pbuf);
	
	switch(USER_LEVEL){
		case STAFF:
		do_stuff(int sockfd, MSG *pbuf);
		case ADMIN:
		do_admin(int sockfd, MSG *pbuf);
		
	}

}
