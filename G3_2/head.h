#ifndef HEAD_H
#define HEAD_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sqlite3.h>
#include <signal.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define DATABASE "my.db"

#define N  64
typedef struct sockaddr SA;

enum CMD{
    LOGIN,  //登录
    STAFF_CHANGE_PASSWD,
    STAFF_QUERY,
    ADMIN_ADD_STAFF,
    ADMIN_DEL_STAFF,
    ADMIN_QUERY,
    SUCCESS,
    FAILED
};

enum USER_LEVEL{
    STAFF = 100,  //普通员工
    ADMIN  //管理员
};

typedef struct
{
    int id;  //员工编号
    char name[N];//姓名
    char addr[N];//地址
    int  age;//年龄
    float salary; //工资
}INFO;

typedef struct{
    int ret;  //操作结果
    int type;//操作类型
    INFO info;//员工信息结构体
    char name[N];//发送消息的户
    char passwd[N];//用户密码在第一次登录时使用
    char data[N];//操作成功或者失败的消息
}MSG;

#endif
