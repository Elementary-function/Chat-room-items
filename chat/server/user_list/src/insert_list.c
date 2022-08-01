/*
 * insert_list.c
 *
 *  Created on: 2011-7-27
 *      Author: 
 */ 

#include "../../include/myhead.h"

/*函数作用：将用户保存到登录链表中
 *输入：登录链表头指针*s，用户名 *user，用户对应的套接字sfd
 *输出：
 *返回值:
 */
void Insert(LNode *s, char *user, int sfd)
{
    LNode *p;
    p = (LNode*) malloc(sizeof(LNode));
    strcpy(p->user, user);
    p->fd = sfd;
    p->next = NULL;
    LNode *q;
    q = s;
    while (q->next != NULL)
    {
        q = q->next;
    }
    q->next = p;
}
