/*
 * myhead.h
 *
 *  Created on: 2011-7-27
 *      Author: 
 */
#ifndef MYHEAD_H_
#define MYHEAD_H_ 

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <sqlite3.h>
#include <fcntl.h>
#include <time.h>

#define LOGIN 0                           /* 宏定义登录的动作为0 */
#define REGIST 1                          /* 宏定义注册的动作为1 */
#define CHATONE 2                         /* 宏定义对单人说话的动作为2 */
#define CHATALL 3                         /* 宏定义注册的动作为3 */
#define CHECK 4                           /* 宏定义查找的动作为4 */
#define HELP 5                            /* 宏定义帮助文档的动作为5 */
#define EXIT 6                            /* 宏定义退出聊天室的动作为6 */
#define EXPRESSION 7                      /* 宏定义表情符号的动作为7 */
#define PHRASE 8                          /* 定义短语的动作为8 */
#define SLIENCE 9                         /* 定义禁言的动作为9 */
#define TICK 10                           /* 定义替人的动作10 */
#define PERMITE 11                        /* 定义解禁的动作为11 */

#define TRANS_FILENAME 12                 /* 定义传输文件名 */
#define TRANS_FILEING 13                  /* 定义传输文件内容 */
#define TRANS_FILE_ACCEPT 14              /* 定义同意接收文件 */
#define TRANS_FILE_REFUSE 15              /* 定义拒绝接收文件 */
#define TRANS_FILE_FINISH 16              /* 定义传输文件完毕 */
#define WRONG_CMD -1                      /* 宏定义错误命令的动作为 -1 */

#define BACK 1                            /* 定义服务器端回传提示信息为1 */
#define CHAT 2                            /* 定义服务器端回传聊天内容为2 */

#define WRONG_CMD -1                      /* 宏定义错误命令的动作为 -1 */

#define TRANS_REFUSE 4
#define port 8000                         /* 宏定义端口号为 8000 */

/*定义数据包 的结构体*/
typedef struct _Message
{
    int action; /* 动作，具体的值已在宏中定义 */
    char message[1000]; /* 存放聊天的内容 */
    char user[20]; /* 存放用户名 */
    char target[20]; /* 存放聊天的目标，具体为某个在线的用户名或all */
    char password[20]; /* 存放密码 */
} Message;

/* 定义服务器端回传信息数据包 */
typedef struct _Back
{
    int type; /* 定义服务器回传数据的类型 */
    char user[20]; /* 定义回传的用户名 */
    char message[1024]; /* 存放回传的信息的内容 */
} Back_Msg;

/*定义存放在线用户或者禁言用户的链表的结构体*/
typedef struct node
{
    char user[20]; /* 用户名 */
    int fd; /* 套接字 */
    struct node *next; /* 链表的下一个指针 */
} LNode;


/* 函数声明 */
void Insert(LNode *, char *, int);
void del(LNode *, int);
int Save_log(char *);
int Save_data(char *);
int Trans_data(char *, int, int, LNode *);
void Log(Message *, LNode *, int);
void Regist(Message *, int);
int is_login(LNode *, char *);
void Chatall(LNode *, LNode *, int, Message *);
void Chatone(LNode *, LNode *, int, Message *);
void Check(LNode *, int, Message *);
void Tick(LNode *, LNode *, int, Message *);
void Slience(LNode *, LNode *, int, Message *);
void Permite(LNode *, LNode *, int, Message *);
void Expression(LNode *, LNode *, int, Message *);
void Phrase(LNode *, LNode *, int, Message *);
void Trans_file(LNode *, int, Message *);

#endif /* MYHEAD_H_ */

