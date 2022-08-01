/*
 * phrase.c
 *
 *  Created on: 2011-7-27
 *      Author: 
 */ 

#include "../../include/myhead.h" 

/*函数作用：处理发送短语
 *输入：当前在线用户的链表的指针*first, 禁言链表s，对应的套接字sfd，数据包的指针*msg
 *输出：向客户端发送相应的字符串
 *返回值: 无
 */
void Phrase(LNode * first, LNode *s, int sfd, Message *msg)
{
    char buffer[1024];
    LNode *p = first->next;

    /* 检查用户是否登录 */
    if (is_login(first, msg->user) == 0)
    {
        strcpy(buffer, "你还没登录!");
        Trans_data(buffer, sfd, BACK, NULL);
        return;
    }

    /* 检查用户是否被禁言 */
    if (is_login(s, msg->user) == 1)
    {
        strcpy(buffer, "你已经被禁言!");
        Trans_data(buffer, sfd, BACK, NULL);
        return;
    }

    /* 检查目标是否在线 */
    if (is_login(first, msg->target) == 0)
    {
        strcpy(buffer, "目标不在线!");
        Trans_data(buffer, sfd, BACK, NULL);
        return;
    }

    time_t t;
    time(&t);
    strcpy(buffer, ctime(&t));
    strcat(buffer, msg->user);
    strcat(buffer, "说：");
    strcat(buffer, msg->target);
    strcat(buffer, msg->message);
    while (p != NULL) /* 遍历登录链表 */
    {
        Trans_data(buffer, p->fd, CHAT, first); /* 将数据包发给每个登录的客户端; */
        p = p->next;
    }
    Save_data(buffer); /* 保存聊天记录 */
}
