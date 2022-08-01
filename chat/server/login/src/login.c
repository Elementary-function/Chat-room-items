/*
 * login.c
 *
 *  Created on: 2011-7-27
 *      Author: 
 */ 

#include "../../include/myhead.h" 

/*函数作用：用户登录
 *输入：客户端发送的请求数据包*client，登录链表头指针*s，用户对应的套接字sfd
 *输出：
 *返回值:
 */
void Log(Message *client, LNode *s, int sfd)
{
    sqlite3 *db = NULL; /* 定义一个数据库文件 */
    char **Result = NULL; /* 定义一个存放字符串的数组老保存查询结果 */
    char *errmsg = NULL; /* 定义保存错误信息 */
    int rc; /* 数据库操作函数的返回值 */
    int nrow; /* 查找的行 */
    int ncolumn; /* 查找的列 */
    char sql[1024]; /* 数据库操作字符串 */
    char buffer[1024]; /* 缓冲区 */
    char log[1024]; /* 日志缓冲区 */
    LNode *p1; /* 用来遍历链表的指针 */

    /* 在数据库中通过用户名查找，结果保存在Result中 */
    rc = sqlite3_open("data.db", &db);
    sprintf(sql, "select * from user_table where name='%s'", client->user);
    rc = sqlite3_get_table(db, sql, &Result, &nrow, &ncolumn, &errmsg);

    /* 先检查是不是超级用户 */
    if (strcmp(client->user, "admin") == 0)
    {
        if (strcmp(client->password, "admin") == 0)
        {
            p1 = s->next;

            /* 检查是否已经登录*/
            while (p1 != NULL)
            {
                if (strcmp(client->user, p1->user) == 0)
                {
                    strcpy(buffer, "你的帐号已登录，不能重复登录");
                    Trans_data(buffer, sfd, BACK, NULL);
                    break;
                }
                if (sfd == p1->fd)
                {
                    strcpy(buffer, "该终端已有用户登录，不可再登录,你已下线");
                    Trans_data(buffer, sfd, BACK, NULL);
                    del(s, sfd);
                    break;
                }
                p1 = p1->next;
            }

            /* 登录成功则提示并保存登录日志 */
            if (p1 == NULL)
            {
                strcpy(buffer, "恭喜你，超级用户登录成功!");
                strcpy(log, client->user);
                strcat(log, "在");
                time_t t;
                time(&t);
                strcat(log, ctime(&t));
                strcat(log, "成功登录\n");
                Save_log(log); /* 保存登录日志 */
                Trans_data(buffer, sfd, BACK, NULL);
                Insert(s, client->user, sfd); /* 加入到在线用户链表中 */
            }
        }
        else
        {
            strcpy(buffer, "登录密码错误!");
            Trans_data(buffer, sfd, BACK, s);
        }
        return;
    }

    /* 然后检查是不是普通用户 */
    else
    {
        if (strlen(Result[3]) == 0) /* 检查是否在数据库中找到该用户 */
        {
            strcpy(buffer, "登录失败，用户未注册");
            Trans_data(buffer, sfd, BACK, s);
        }
        else
        {
            if (strcmp(client->password, Result[3]) != 0) /* 比对输入的密码于数据库中的密码是否相同 */
            {
                strcpy(buffer, "密码错误");
                Trans_data(buffer, sfd, BACK, NULL);
            }
            else
            {

                /* 检查是否已经登录 */
                p1 = s->next;
                while (p1 != NULL)
                {
                    if (strcmp(client->user, p1->user) == 0)
                    {
                        strcpy(buffer, "你的帐号已登录，不能重复登录");
                        Trans_data(buffer, sfd, BACK, NULL);
                        break;
                    }
                    if (sfd == p1->fd)
                    {
                        strcpy(buffer, "该终端已有用户登录，不可再登录,你已下线");
                        Trans_data(buffer, sfd, BACK, NULL);
                        del(s, sfd);
                        break;
                    }
                    p1 = p1->next;
                }

                /* 普通用户登录成功 */
                if (p1 == NULL)
                {
                    strcpy(buffer, "恭喜你,登录成功!");
                    strcpy(log, client->user);
                    strcat(log, "在");
                    time_t t;
                    time(&t);
                    strcat(log, ctime(&t));
                    strcat(log, "成功登录\n");
                    Save_log(log); /* 保存登录日志 */
                    Trans_data(buffer, sfd, BACK, NULL);
                    Insert(s, client->user, sfd); /* 添加用户到在线用户链表中 */
                }
            }
        }
    }
    sqlite3_free_table(Result);
    sqlite3_close(db);
}
