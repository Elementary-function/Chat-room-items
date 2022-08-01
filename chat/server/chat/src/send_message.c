/*
 * send_message.c
 *
 *  Created on: 2011-7-27
 *      Author: 
 */ 

#include "../../include/myhead.h" 

/*函数作用：向客户端发送信息
 *输入：发送的内容buffer，用户对应的套接字sfd，发送的类型 type，在线用户链表s（不需要则为NULL)
 *输出：向客户端发送打包好的消息
 *返回值: 成功返回1
 */
int Trans_data(char *buffer, int sfd, int type, LNode *s)
{
    Back_Msg msg;
    strcpy(msg.message, buffer);
    msg.type = type;
    if (type == CHAT)
    {
        LNode *p;
        p = s->next;
        while (p != NULL)
        {
            if (p->fd == sfd)
            {
                strcpy(msg.user, p->user);
                break;
            }
            p = p->next;
        }
    }
    write(sfd, &msg, sizeof(msg));
    return 1;
}
