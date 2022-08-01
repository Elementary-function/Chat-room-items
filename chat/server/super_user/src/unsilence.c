/*
 * unsilence.c
 *
 *  Created on: 2011-7-27
 *      Author: 
 */ 

#include "../../include/myhead.h" 

/*函数作用：解禁已被禁言的对象
 *输入：登录链表头指针s1, 禁言链表s2，当前发消息的客户端连接符sfd，客户端发来的消息包msg
 *输出：
 *返回值:
 */
void Permite(LNode *s1, LNode *s2, int sfd, Message *msg)
{
    LNode *p1;
    p1 = s1->next;
    char buffer[1024];
    if ((strcmp(msg->user, "admin") == 0) && (strcmp(msg->password, "admin")
            == 0)) /* 检查当前是不是超级用户 */
    {
        /* 找到并解禁用户 */
        while (p1 != NULL)
        {
            if (strcmp(msg->target, p1->user) == 0)
            {
                del(s2, p1->fd);
                strcpy(buffer, "恭喜你已被解禁");
                Trans_data(buffer, p1->fd, BACK, NULL);
                strcpy(buffer, "用户已被成功解禁");
                Trans_data(buffer, sfd, BACK, NULL);
                break;
            }
            p1 = p1->next;
        }

        /* 错误的目标 */
        if (p1 == NULL)
        {
            strcpy(buffer, "用户没有登录");
            Trans_data(buffer, sfd, BACK, NULL);
        }
    }

    /* 当前不是超级用户 */
    else
    {
        strcpy(buffer, "你无权解禁用户");
        Trans_data(buffer, sfd, BACK, NULL);
    }
}
