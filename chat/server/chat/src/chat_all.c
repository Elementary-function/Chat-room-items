/*
 * chat_all.c
 *
 *  Created on: 2011-7-27
 *      Author: 
 */ 

#include "../../include/myhead.h"

/*函数作用：对所有人聊天
 *输入：登录链表头指针first,禁言链表s，套接字sfd，从客户端来的数据包msg
 *输出：成功则向客户端输出聊天内容
 *返回值:
 */
void Chatall(LNode * first, LNode *s, int sfd, Message *msg)
{
    char buffer[1024]; /* 定义缓冲区 */
    bzero(buffer, 1024);
    LNode *p = first->next;

    /* 检查是否已登录 */
    if (is_login(first, msg->user) == 0)
    {
        strcpy(buffer, "你还没登录!");
        Trans_data(buffer, sfd, BACK, NULL);
        return;
    }

    /* 检查是否被禁言 */
    if (is_login(s, msg->user) == 1)
    {
        strcpy(buffer, "你已被禁言，不能发消息!");
        Trans_data(buffer, sfd, BACK, NULL);
        return;
    }

    /* 将消息发送给客户端 */
    time_t t;
    time(&t);
    strcpy(buffer, ctime(&t));
    strcpy(buffer, msg->user);
    strcat(buffer, "对大家说: ");
    strcat(buffer, msg->message);
    while (p != NULL) /* 遍历登录链表 */
    {
        Trans_data(buffer, p->fd, CHAT, first); /* 将数据包发给每个登录的客户端 */
        p = p->next;
    }

    /* 保存聊天日志 */
    Save_data(buffer);
}
