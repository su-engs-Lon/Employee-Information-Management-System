#ifndef HEAD_H
#define HEAD_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sqlite3.h>
#include <signal.h>
#include <time.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define DATABASE "my.db"

#define N  64
typedef struct sockaddr SA;
//各种命令
enum CMD{
	LOGIN,  //登录
	STAFF_CHANGE_PASSWD,//修改密码
	STAFF_QUERY,        //员工查询
	ADMIN_ADD_STAFF,    //管理员增加员工
	ADMIN_DEL_STAFF,    //管理员删除员工
	ADMIN_QUERY,        //管理员查询
	QUIT ,            //退出
	FAILED              //失败
};

enum USER_LEVEL{
    STAFF = 100,  //普通员工
    ADMIN  //管理员
};
//员工信息结构体
typedef struct
{
	int id;  //员工编号
	char name[N];//姓名
	char addr[N];//地址
	int  age;//年龄
	int salary; //工资
}INFO;
//所有信息的结构体
typedef struct{
	int USER_LEVEL;
	int ret;  //操作结果
	int type;//操作类型
	INFO info;//员工信息结构体
	char name[N];//发送消息的户
	char passwd[N];//用户密码在第一次登录时使用
	char data[N];//操作成功或者失败的消息
}MSG;

#endif
