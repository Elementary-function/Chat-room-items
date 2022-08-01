/*
 * delete_list.c
 *
 *  Created on: 2011-7-27
 *      Author: 
 */ 

#include "../../include/myhead.h" 

/*函数作用：删除链表中的某个用户
 *输入：登录链表头指针*s，用户对应的套接字sfd
 *输出：
 *返回值:
 */
void del(LNode *s, int sfd)
{
    LNode *p;
    LNode *q;
    p = s;
    q = s->next;
    while (p->next != NULL)
    {
        if (q->fd == sfd)
        {
            p->next = q->next;
            free(q);
            break;
        }
        p = p->next;
        q = p->next;
    }
}
