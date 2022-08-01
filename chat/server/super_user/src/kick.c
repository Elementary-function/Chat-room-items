/*
 * check_putin.c
 *
 *  Created on: 2011-7-27
 *      Author: 
 */ 

#include "../../include/myhead.h"

/*函数作用：超级用户踢人
 *输入：登录链表头指针s,当前发消息的客户端连接符sfd，客户端发来的消息包msg
 *输出：
 *返回值:
 */
void Tick(LNode *s, LNode *s2, int sfd, Message *msg) /* 踢出在线用户 */
{
    LNode *p1; /* 定义一个指针遍历在线用户链表 */
    p1 = s->next;
    char buffer[1024]; /* 缓冲区 */
    if ((strcmp(msg->user, "admin") == 0) && (strcmp(msg->password, "admin")
            == 0)) /* 检查当前用户是不是超级用户 */
    {
        /* 检查目标用户是不是超级用户(其实也没有必要，为什么要踢出自己） */
        if (strcmp(msg->target, "admin") == 0)
        {
            strcpy(buffer, "不可踢出超级用户!");
            Trans_data(buffer, sfd, BACK, NULL);
            return;
        }

        /* 找到目标并踢下线 */
        while (p1 != NULL)
        {
            if (strcmp(msg->target, p1->user) == 0)
            {
                del(s, p1->fd); /* 从在线用户中删除 */
                del(s2, p1->fd); /* 从禁言用户中删除 */
                strcpy(buffer, "很遗憾，你已被踢下线");
                Trans_data(buffer, p1->fd, BACK, NULL);
                strcpy(buffer, "用户成功被踢下线");
                Trans_data(buffer, sfd, BACK, NULL);
                break;
            }
            p1 = p1->next;
        }

        /* 如果没有找到目标，那么输出目标不在线 */
        if (p1 == NULL)
        {
            strcpy(buffer, "用户已不在线");
            Trans_data(buffer, sfd, BACK, NULL);
        }
    }

    /* 如果当前不是超级用户，提示 */
    else
    {
        strcpy(buffer, "你无权踢出用户");
        Trans_data(buffer, sfd, BACK, NULL);
    }
}
 
