/*
 * chat_one.c
 *
 *  Created on: 2011-7-27
 *      Author: 
 */ 

#include "../../include/myhead.h"

/*函数作用：对某个人聊天
 *输入：登录链表头指针first,禁言链表s，套接字sfd，客户端来的数据包msg
 *输出：聊天成功则向目标发送聊天内容
 *返回值:
 */
void Chatone(LNode * first, LNode * s, int sfd, Message *msg)
{
    char buffer[1024]; /* 缓冲区 */
    char his[1024]; /* 聊天记录 */
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
        strcpy(buffer, "你已被禁言,不能发消息!");
        Trans_data(buffer, sfd, BACK, NULL);
        return;
    }

    time_t t;
    time(&t);

    /* 聊天内容 */
    strcpy(buffer, ctime(&t));
    strcat(buffer, msg->user);
    strcat(buffer, "对你悄悄说： ");
    strcat(buffer, msg->message);

    /* 聊天记录信息 */
    strcpy(his, ctime(&t));
    strcat(his, msg->user);
    strcat(his, "悄悄的对");
    strcat(his, msg->target);
    strcat(his, "说:");
    strcat(his, msg->message);

    /* 发送消息并保存聊天记录 */
    while (p != NULL)
    {
        if (strcmp(p->user, msg->target) == 0) /* 匹配目标用户名和登录用户名 */
        {
            Trans_data(his, sfd, CHAT, first);
            Trans_data(buffer, p->fd, CHAT, first);
            Save_data(his);
            return;
        }
        p = p->next;
    }

    /* 如果没有找到目标则返回提示信息 */
    strcpy(buffer, "目标还没登录！");
    Trans_data(buffer, sfd, BACK, NULL);
}

