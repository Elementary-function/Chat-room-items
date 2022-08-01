/*
 * silence.c
 *
 *  Created on: 2011-7-27
 *      Author: 
 */ 

#include "../../include/myhead.h" 

/*函数作用：超级用户禁言
 *输入：登录链表头指针s1,禁言列s2， 当前发消息的客户端连接符sfd，客户端发来的消息包msg
 *输出：
 *返回值:
 */
void Slience(LNode *s1, LNode *s2, int sfd, Message *msg)
{
    LNode *p1; /* 建立一个指针来遍历链表 */
    p1 = s1->next;
    char buffer[1024];
    if ((strcmp(msg->user, "admin") == 0) && (strcmp(msg->password, "admin")
            == 0)) /* 检查当前是不是超级用户 */
    {

        /* 检查目标是不是超级用户 */
        if (strcmp(msg->target, "admin") == 0)
        {
            strcpy(buffer, "不可禁言超级用户!");
            Trans_data(buffer, sfd, BACK, NULL);
            return;
        }

        /* 检查目标是不是已经被禁言 */
        if (is_login(s2, msg->target) == 1)
        {
            strcpy(buffer, "该用户已被禁言!");
            Trans_data(buffer, sfd, BACK, NULL);
            return;
        }

        /* 找到目标并禁言他 */
        while (p1 != NULL)
        {
            if (strcmp(msg->target, p1->user) == 0)
            {
                Insert(s2, msg->target, p1->fd);
                strcpy(buffer, "很遗憾，你已被禁言");
                Trans_data(buffer, p1->fd, BACK, NULL);
                strcpy(buffer, "用户已被成功禁言");
                Trans_data(buffer, sfd, BACK, NULL);
                break;
            }
            p1 = p1->next;
        }

        /* 如果没有找到那么目标不在线 */
        if (p1 == NULL)
        {
            strcpy(buffer, "该用户不在线,不需禁言");
            Trans_data(buffer, sfd, BACK, NULL);
        }
    }

    /* 不是超级用户的话没有禁言权限 */
    else
    {
        strcpy(buffer, "你无权禁言用户");
        write(sfd, buffer, 1024);
    }
}
