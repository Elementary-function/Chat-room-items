/*
 * check_online.c
 *
 *  Created on: 2011-7-27
 *      Author: 
 */ 

#include "../../include/myhead.h" 

/*函数作用：向客户端反馈登录的用户名
 *输入：登录链表头指针first,当前发消息的客户端连接符sfd，客户端发来的消息包msg
 *输出：
 *返回值:
 */
void Check(LNode * first, int sfd, Message *msg)
{
    char buffer[1024];
    bzero(buffer, 1024);
    LNode *p = first->next;

    /* 检查是否已登录 */
    if (is_login(first, msg->user) == 0)
    {
        strcpy(buffer, "你还没登录！");
        Trans_data(buffer, sfd, BACK, NULL);
        return;
    }

    /* 发送在线用户消息 */
    strcpy(buffer, "当前在线用户有：\n");
    while (p != NULL)
    {
        strcat(buffer, p->user);
        buffer[strlen(buffer)] = '\n';
        p = p->next;
    }
    Trans_data(buffer, sfd, BACK, NULL);
}
