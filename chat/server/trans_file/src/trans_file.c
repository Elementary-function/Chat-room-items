/*
 * check_putin.c
 *
 *  Created on: 2011-7-27
 *      Author: 
 */ 

#include "../../include/myhead.h"

/*函数作用：服务器端实现文件的点对点传送
 *输入：登录链表头指针, 对应的套接字sfd，接收到的数据包*msg
 *输出：向目标客户端发送数据
 *返回值：
 */
void Trans_file(LNode* first, int sfd, Message *msg)
{
    int fd;
    LNode *p = first->next;
    Back_Msg msgc;

    /* 判断用户是否登录 */
    if (is_login(first, msg->user) == 0)
    {
        Trans_data("你还没有登录", sfd, TRANS_FILE_REFUSE, NULL);
        return;
    }

    /* 判断目标是否登录 */
    if(is_login(first,msg->target) == 0)
    {
        Trans_data("目标还没有登录", sfd, TRANS_FILE_REFUSE, NULL);
        return;
    }
    /* 找出目标用户名对应的fd */
    while(p != NULL)
    {
        if(strcmp(p->user,msg->target) == 0)
        {
            fd = p->fd;
            break;
        }
        p = p->next;
    }

    /*发送给对象客户端 */
    msgc.type = msg->action;
    strcpy(msgc.message, msg->message);
    strcpy(msgc.user, msg->user);
    write(fd,&msgc,sizeof(msgc));
}
 
