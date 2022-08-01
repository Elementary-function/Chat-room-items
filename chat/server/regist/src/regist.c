/*
 * regist.c
 *
 *  Created on: 2011-7-27
 *      Author: 
 */ 

#include "../../include/myhead.h"

/*函数作用：用户注册
 *输入：客户端发送的请求数据包*client，用户对应的套接字sfd
 *输出：在data.db数据库中保存成功注册用户的名字和密码
 *返回值:
 */
void Regist(Message *client, int sfd)
{
    static sqlite3 *db = NULL; /* 定义一个数据库文件 */
    static char *errmsg = NULL; /* 定义保存错误信息 */
    int rc; /* 数据库操作函数返回值 */
    char sql[1024]; /* 数据苦操作字符串 */
    char buffer[1024]; /* 定义缓冲区 */

    /* 在数据库中插入新用户和密码 */
    rc = sqlite3_open("data.db", &db);
    sprintf(sql, "insert into user_table values('%s','%s')", client->user,
            client->password);
    rc = sqlite3_exec(db, sql, 0, 0, &errmsg);

    /* 插入失败 */
    if (rc)
    {
        strcpy(buffer, "注册失败,用户已存在!");
        Trans_data(buffer, sfd, BACK, NULL);
    }

    /* 插入成功 */
    else
    {
        strcpy(buffer, "恭喜你,注册成功!");
        Trans_data(buffer, sfd, BACK, NULL);
    }
    sqlite3_close(db);
}

